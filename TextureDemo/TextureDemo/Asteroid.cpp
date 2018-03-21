#include "Asteroid.h"

Asteroid::Asteroid(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	player = playerEntity;
	width = 0.1;
	height = 0.1;
	mass = 5;
	type = asteroid;
}

void Asteroid::update(double deltaTime) {
	//DynamicGameEntity::update(deltaTime, player->getPosition);
	//printf("%f", player->getPosition().x);
	screenPosition = position - player->getPosition();
}