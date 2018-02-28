#include "Player.h"

Player::Player(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: Ship(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{

}

void Player::update(double deltaTime) {
	position += velocity * (float)deltaTime;

	std::cout << position.x << ", " << position.y << std::endl;
}
