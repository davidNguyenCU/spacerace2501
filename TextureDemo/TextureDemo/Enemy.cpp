#include "Enemy.h"

Enemy::Enemy(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity )
	: Ship(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements), player(playerEntity) 
{

}

void Enemy::update(double deltaTime) {
	Ship::update(deltaTime, player->getPosition());
}

void Enemy::setPosition(glm::vec3 updatedPosition) { position = updatedPosition; }
void Enemy::setVelocity(glm::vec3 updatedVelocity) { velocity = updatedVelocity; }
void Enemy::setAcceleration(glm::vec3 updatedAcceleration) { acceleration = updatedAcceleration; }