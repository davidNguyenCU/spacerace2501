#pragma once

#include "Ship.h"

class Player : public Ship {
public:
	Player(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
};