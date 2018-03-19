#include "Asteroid.h"

Asteroid::Asteroid(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	player = playerEntity;
}

void Asteroid::update(double deltaTime) {
	//DynamicGameEntity::update(deltaTime, player->getPosition);
	//printf("%f", player->getPosition().x);
	screenPosition = position - player->getPosition();
}