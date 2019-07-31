#include "Bullet.h"

Bullet::Bullet(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: DynamicGameEntity(entityPos, entityVelocity, acceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	//bulletTexture = RenderedObject(entityTexture);
}