#include "RocketBullet.h"

RocketBullet::RocketBullet(glm::vec3 &entityPos, glm::vec3 entityDirection, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: Bullet(entityPos, entityDirection * 0.2f, glm::vec3(0.2f, 0.2f, 0.0f), entityRotationAmount, entityTexture, entityNumElements)
{
}

void RocketBullet::update(double deltaTime) {
	Bullet::update(deltaTime);
	//position = glm::vec3(0.0f);
	position += glm::vec3(0.02f, 0.02f, 0.0f);
	cout << "Position: (" << position.x << ", " << position.y << ")    (" << scale.x << ", " << scale.y << ")" << endl;
}