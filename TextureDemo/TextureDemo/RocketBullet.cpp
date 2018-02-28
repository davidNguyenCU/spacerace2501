#include "RocketBullet.h"

RocketBullet::RocketBullet(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: Bullet(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
}

void RocketBullet::update(double deltaTime) {
	position += velocity * (float)deltaTime;
}