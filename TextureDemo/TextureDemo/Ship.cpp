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