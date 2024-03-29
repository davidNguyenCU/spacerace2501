#include "Ship.h"
#include "Map.h"

const float Ship::MAX_FORWARD_VELOCITY = 2.0f;
const float Ship::MAX_FORWARD_ACCELERATION = 0.5f;
const float Ship::MAX_SIDE_VELOCITY = 1.5f;
const float Ship::MAX_SIDE_ACCELERATION = 4.0f;

Ship::Ship(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint &turretTex, GLint entityNumElements)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	gunAmmo = MAX_GUN_AMMO;
	rocketAmmo = MAX_ROCKET_AMMO;

	type = ship;
	mass = 50.0f;
	width = 0.175;
	height = 0.175;

	sideVelocity = 0;

	bashStartPosition = 0;
	bashVelocity = 0;
	bashAccler = 1500;
	bashDirection = 0;

	bashStarted = false;
	isBashing = false;
	bashCooldown = false;

	health = MAX_HEALTH;

	turretRot = 90.0f;

	dashType = 0;
	//Dash type 0 for bashing, 1 for blinking

	turretSprite = RenderedObject(turretTex);
}

void Ship::update(double deltaTime, glm::vec3 playerPosition) {
	if (momentum.y < -5) {
		momentum.y = -5;
	}

	if (momentum.y > 125.0) 
	{
		momentum.y -= momentum.y*deltaTime*0.95;
	}

	/*if (velocity.x > MAX_SIDE_VELOCITY) {
		velocity.x = MAX_SIDE_VELOCITY;
	}
	else if (velocity.x < -1 * MAX_SIDE_VELOCITY) {
		velocity.x = -1 * MAX_SIDE_VELOCITY;
	}

	if (acceleration.y < 0.0f) {
		acceleration.y = 0.0f;
	}
	else if (acceleration.y > MAX_FORWARD_ACCELERATION) {
		acceleration.y = MAX_FORWARD_ACCELERATION;
	}

	if (acceleration.x > MAX_SIDE_ACCELERATION) {
		acceleration.x = MAX_SIDE_ACCELERATION;
	}
	else if (acceleration.x < -1 * MAX_SIDE_ACCELERATION) {
		acceleration.x = -1 * MAX_SIDE_ACCELERATION;
	}*/

	if (isOutOfBounds()) {
		momentum *= 0.95;
		outOfBounds(deltaTime);
	}

	//std::cout << "Vertical Motion ->  Accleration: " << acceleration.y << ", \tVelocity : " << velocity.y << std::endl;
	//std::cout << "Health: " << health << std::endl;

	//DynamicGameEntity::update(deltaTime, playerPosition);

	acceleration = momentum / mass;
	velocity = momentum * 1.0f / mass;

	if (velocity.x > MAX_SIDE_VELOCITY) {
		velocity.x = MAX_SIDE_VELOCITY;
	}
	else if (velocity.x < -1 * MAX_SIDE_VELOCITY) {
		velocity.x = -1 * MAX_SIDE_VELOCITY;
	}

	if (velocity.y < 0.0f)
	{
		velocity.y = 0.0f;
	}

	position += velocity * (float)deltaTime;
	screenPosition = position - playerPosition;

}

void Ship::render(Shader &shader) {
	//std::cout << turretRot << std::endl;
	turretSprite.render(screenPosition, scale / 1.5f, turretRot, numElements, shader);
	DynamicGameEntity::render(shader);
}

void Ship::setTurret(glm::vec3 aimingAt) {
	glm::vec3 direction(aimingAt - position);
	turretRot = 180.0 / 3.14159 * atan2f(direction.y, direction.x);
}

//Side to side movement with A and D keys
void Ship::sideMovement(int state, double deltaTime) {
	if (state == 1) {
		momentum.x += 5;
		//position.x += sideVelocity * deltaTime; 
	}
	else if (state == -1) {
		momentum.x -= 5;
		//position.x -= sideVelocity * deltaTime; 
	}
	else
		momentum.x += 0;
}

//Side dashing with Q and E key
void Ship::sideBash(int state, double currentTime, double deltaTime) {
	//printf("%d", state);
	//Initial state to begin dashing, check if not bashing and if cooldown is not going
	if (state != 0
		&& bashStarted == false
		&& bashCooldown == false) {
	
		bashStarted = true;
		bashCooldown = true;
		bashDirection = state;
	}

	
	//Reset the bool if we started bashing, save the position of the bash start and time for cooldown
	if (bashStarted == true) {
		if (bashDirection == 1){
			if (dashType == 0)
				momentum.x += 100.0;
			else if (dashType == 1)
				position.x += 0.375;
		}
		else if (bashDirection == -1){
			if (dashType == 0)
				momentum.x -= 100.0;
			else if (dashType == 1)
				position.x -= 0.375;
		}

		bashStartPosition = position.x;
		timeOfBashStart = currentTime;
		//momentum.x = 0;
		bashStarted = false;
	}

	//Check if cooldown time has passed, if has, uncheck cooldown boolean
	if (bashCooldown == true){
		if (currentTime - timeOfBashStart > 2.0)
			bashCooldown = false;
	}
	//If in the midst of bashing, adjust the side velocity (and subsequently its position)
	/*
	if (isBashing == true) {
		if (bashDirection == 1 && position.x < bashStartPosition + 0.35)
			momentum.x += 0.01;
		else if (bashDirection == -1 && position.x > bashStartPosition - 0.35)
			momentum.x += -0.01;
		else if(position.x < bashStartPosition - 0.35 || position.x > bashStartPosition + 0.35){
			momentum.x = 0;
			isBashing = false;
		}
	}*/
}

void Ship::hasShotGun() {
	gunTimer = gunCooldown;
	gunAmmo--;
}

void Ship::hasShotRocket() {
	rocketTimer = rocketCooldown;
	rocketAmmo--;
}

void Ship::updateBulletTimers(double deltaTime) {
	gunTimer -= deltaTime;
	rocketTimer -= deltaTime;
}

bool Ship::canShootGun() {
	return (gunTimer <= 0.0f && gunAmmo > 0);
}

bool Ship::canShootRocket() {
	return (rocketTimer <= 0.0f && rocketAmmo > 0);
}

void Ship::outOfBounds(double deltaTime) {
	//std::cout << "To subtract: " << 20.0 * deltaTime << std::endl;
	health = health - (20.0 * deltaTime);
	if (health < 0.0) health = 0.0;
}

bool Ship::isOutOfBounds() {
	return (position.x < -(0.5 * Map::getRoadWidth()) || position.x > 0.5 * Map::getRoadWidth());
}


