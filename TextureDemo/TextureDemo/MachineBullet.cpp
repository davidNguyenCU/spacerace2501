#include "MachineBullet.h"

MachineBullet::MachineBullet(glm::vec3 &entityPos, glm::vec3 entityDirection, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: Bullet(entityPos, entityDirection * 0.2f, glm::vec3(0.2f, 0.2f, 0.0f), entityRotationAmount, entityTexture, entityNumElements)
{
}

void MachineBullet::update(double deltaTime) {
	//cout << "Machine Bullet Pos: " << position.x << ", " << position.y << endl;
	Bullet::update(deltaTime);
}