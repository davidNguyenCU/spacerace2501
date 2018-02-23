#include "Ship.h"

Ship::Ship(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
}

void Ship::update(double deltaTime) {
	position.x = 0.8f * sin(glfwGetTime());
}