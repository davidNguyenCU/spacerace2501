#include "MachineBullet.h"

MachineBullet::MachineBullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity)
	: Bullet(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements, bulletVelocity)
{
}

void MachineBullet::update(double deltaTime) {
	position.x = 0.8f * sin(glfwGetTime());
}