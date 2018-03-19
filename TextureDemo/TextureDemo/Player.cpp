#include "Player.h"

Player::Player(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: Ship(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	tint = glm::vec3(4.0f, 4.0f, 0.0f);
}