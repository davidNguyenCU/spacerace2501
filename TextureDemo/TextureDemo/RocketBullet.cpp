#include "RocketBullet.h"

RocketBullet::RocketBullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity)
	: Bullet(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, bulletVelocity)
{
}
//Testing

void RocketBullet::update(double deltaTime) {
	position += velocity * (float)deltaTime;
}