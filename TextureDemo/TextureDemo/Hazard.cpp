#include "Hazard.h"

Hazard::Hazard(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
}

void Hazard::update(double deltaTime) {
	position.x = 0.8f * sin(glfwGetTime());
}