#include "Pickup.h"

Pickup::Pickup(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	width = 0.125;
	height = 0.125;
}

void Pickup::update(double deltaTime, glm::vec3 playerPosition) {
	DynamicGameEntity::update(deltaTime, playerPosition);
}

void Pickup::swapActiveState()
{
	if (getActiveState() == true) { setActiveState(false); }
	else { setActiveState(true); }
}
