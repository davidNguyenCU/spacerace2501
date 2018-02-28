#include "MachineBullet.h"

MachineBullet::MachineBullet(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: Bullet(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
}

void MachineBullet::update(double deltaTime) {
	position.x = 0.8f * sin(glfwGetTime());
}