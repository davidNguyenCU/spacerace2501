#include "PowerUp.h"

PowerUp::PowerUp(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint &turretTex ,GLint entityNumElements, Type typeOfPowerup)
	: Ship(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, turretTex, entityNumElements)
{
	typeOfPowerup = type;
}

void PowerUp::updatePos(double deltaTime) 
{
	position.x = 0.5f * sin(glfwGetTime());
}

//void PowerUp::render(Shader shader){
//	DynamicGameEntity::render(shader);
//}