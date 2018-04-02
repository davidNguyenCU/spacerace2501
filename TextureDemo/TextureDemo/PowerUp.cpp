#include "PowerUp.h"

PowerUp::PowerUp(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Type typeOfPowerup)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	typeOfPowerup = type;
}

void PowerUp::updatePos(double deltaTime) 
{
	position.x = 0.5f * sin(glfwGetTime());
}