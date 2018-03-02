#include "Ship.h"

Ship::Ship(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	currentGun = MachineGun;
	gunAmmo = MAX_GUN_AMMO;
	rocketAmmo = MAX_ROCKET_AMMO;

	bashStartPosition = 0;
	bashVelocity = 0;
	bashAccler = 50;
	bashDirection = 0;

	bashStarted = false;
	isBashing = false;
	bashCooldown = false;
}

void Ship::update(double deltaTime, glm::vec3 playerPosition) {
	if (velocity.y < 0.0f) velocity.y = 0.0f;
	DynamicGameEntity::update(deltaTime, playerPosition);
}

Ship::GunType Ship::getCurrentGun() {
	return currentGun;
}

/*void Ship::shootRocket(glm::vec2 target, GLuint texture, int size) {
	if (rocketAmmo <= 0 || rockets.size() >= 5) return;
	std::cout << "Num rockets " << rockets.size() << std::endl;

	glm::vec3 direction = glm::normalize(glm::vec3(target, 0.0f) - position);
	
	rockets.push_back(RocketBullet(position, direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), rotationAmount, texture, size));
}

void Ship::shootGun(glm::vec2 target, GLuint texture, int size) {
	if (gunAmmo <= 0 || bullets.size() >= 5) return;

	glm::vec3 direction = glm::normalize(glm::vec3(target, 0.0f) - position);

	bullets.push_back(MachineBullet(position, direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), rotationAmount, texture, size));
	std::cout << "Num bullets: " << bullets.size() << std::endl;
}*/

void Ship::switchGun() {
	switch (currentGun) {
	case MachineGun:
		currentGun = Rocket;
	case Rocket:
		currentGun = MachineGun;
	}
}

void Ship::render(Shader& shader) {
	DynamicGameEntity::render(shader);

	/*for (auto &bullet : bullets) {
		bullet.render(shader);
	}

	for (auto &rocket : rockets) {
		rocket.render(shader);
	}*/
}


void Ship::sideMovement(int state, double deltaTime) {
	if (state == 1) { position.x += 0.55 * deltaTime; }
	else if (state == -1) { position.x -= 0.55 * deltaTime; }
}

void Ship::sideBash(int state, double currentTime, double deltaTime) {

	if (state != 0
		&& isBashing == false
		&& bashStarted == false
		&& bashCooldown == false) {
	
		isBashing = true;
		bashStarted = true;
		bashCooldown = true;
		bashDirection = state;
	}

	if (bashStarted == true) {
		bashStartPosition = position.x;
		timeOfBashStart = currentTime;
		bashStarted = false;
	}

	if (bashCooldown == true){
		if (currentTime - timeOfBashStart > 4.0)
			bashCooldown = false;
	}

	if (isBashing == true) {

		if (bashDirection == 1 && position.x < bashStartPosition + 0.35)
			bashVelocity += bashAccler * deltaTime;
		else if (bashDirection == -1 && position.x > bashStartPosition - 0.35)
			bashVelocity -= bashAccler * deltaTime;
		else if(position.x < bashStartPosition - 0.35 || position.x > bashStartPosition + 0.35){
			bashVelocity = 0;
			isBashing = false;
		}
	}

	position.x += bashVelocity * deltaTime;


}