#include "RocketBullet.h"

RocketBullet::RocketBullet(glm::vec3 &entityPos, glm::vec3 entityDirection, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: Bullet(entityPos, entityDirection, glm::vec3(0.2f, 0.2f, 0.0f), entityRotationAmount, entityTexture, entityNumElements)
{
	//cout << velocity.x << velocity.y << endl;
}