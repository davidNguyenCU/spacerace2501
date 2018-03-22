#include "Player.h"

Player::Player(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint &turretTex, GLint entityNumElements)
	: Ship(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, turretTex, entityNumElements)
{
	tint = glm::vec3(1.0f, 0.8f, 0.2f);
}

void Player::update(double deltaTime, glm::vec3 mousePos) {
	Ship::update(deltaTime, position);
	setTurret(mousePos);
}

void Player::render(Shader &shader)
{
	shader.setUniform3f("tint", tint);
	Ship::render(shader);
}

void Player::setTurret(glm::vec3 aimingAt) {
	glm::vec3 modifiedPos(position + aimingAt);
	Ship::setTurret(modifiedPos);
}