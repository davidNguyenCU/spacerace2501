#pragma once

#include "DynamicGameEntity.h"

class Asteroid : public GameEntity {
public:
	Asteroid(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
};