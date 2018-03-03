#include "Ship.h"

Ship::Ship(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	//currentGun = MachineGun;
	gunAmmo = MAX_GUN_AMMO;
	rocketAmmo = MAX_ROCKET_AMMO;

	gunTimer = 0.5f;
	rocketTimer = 0.5f;

	bashStartPosition = 0;
	bashVelocity = 0;
	bashAccler = 50;
}

void Ship::update(double deltaTime, glm::vec3 playerPosition) {
	if (velocity.y < 0.0f) velocity.y = 0.0f;
	DynamicGameEntity::update(deltaTime, playerPosition);

	updateBulletTimers(deltaTime);
}

void Ship::updateBulletTimers(double deltaTime) {
	if (gunTimer > 0.0f) {
		gunTimer -= deltaTime;
		if (gunTimer < 0.0f) gunTimer = 0.0f;
	}

	if (rocketTimer > 0.0f) {
		rocketTimer -= deltaTime;
		if (rocketTimer < 0.0f) rocketTimer = 0.0f;
	}
}

void Ship::render(Shader& shader) {
	DynamicGameEntity::render(shader);
}


void Ship::sideMovement(int state, double deltaTime) {
	if (state == 1) { position.x += 0.55 * deltaTime; }
	else if (state == -1) { position.x -= 0.55 * deltaTime; }
}

void Ship::recordShipBashStart(float bashingStartPosition, double bashTimeStart) {
	bashStartPosition = bashingStartPosition;
	timeOfBashStart = bashTimeStart;
}

bool Ship::sideBash(bool bashing, int bashDirection, double deltaTime, double currentTime) {
	if (currentTime - timeOfBashStart > 2)
		ableToBashAgain = true;
	else
		ableToBashAgain = false;


	if (bashing == true) {

		if(bashDirection == 1) bashVelocity += bashAccler * deltaTime;
		else if (bashDirection == -1) bashVelocity -= bashAccler * deltaTime;
		position.x += bashVelocity * deltaTime;
		if (position.x > bashStartPosition + 0.25 || position.x < bashStartPosition - 0.25) {
			bashVelocity = 0;
			return false;
		}
	}
	else if (bashing == false) {
		bashVelocity = 0;
		position.x += bashVelocity;
		return false;
	}
	else { return true; }
}

void Ship::hasShotGun() {
	gunTimer = gunCooldown;
	gunAmmo--;
}

void Ship::hasShotRocket() {
	rocketTimer = rocketCooldown;
	rocketAmmo--;
}

bool Ship::canShootGun() { return (gunAmmo > 0 && gunTimer <= 0.0f); }

bool Ship::canShootRocket() { return (rocketAmmo > 0 && rocketTimer <= 0.0f); }
