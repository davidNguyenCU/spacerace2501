#include "Ship.h"

Ship::Ship(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	currentGun = MachineGun;
	gunAmmo = 10;
	rocketAmmo = 2;
}

void Ship::update(double deltaTime) {
	//position.x = 0.8f * sin(glfwGetTime());
} 

Ship::GunType Ship::getCurrentGun() {
	return currentGun;
}

void Ship::shootRocket(glm::vec2 target) {
	std::cout << "Shooting Rocket" << std::endl;
}

void Ship::shootGun(glm::vec2 target) {
	std::cout << "Shooting Gun" << std::endl;
}

void Ship::switchGun() {
	switch (currentGun) {
	case MachineGun:
		currentGun = Rocket;
	case Rocket:
		currentGun = MachineGun;
	}
}

