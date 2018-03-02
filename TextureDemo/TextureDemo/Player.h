#pragma once

#include "Ship.h"

class Player : public Ship {
public:
	Player(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);
	glm::vec3 getVelocity() { return velocity; }
	virtual void update(double deltaTime) override;
};