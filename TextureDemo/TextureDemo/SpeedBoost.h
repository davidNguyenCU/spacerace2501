#pragma once

#include "GameEntity.h"

class SpeedBoost : public GameEntity {
public:
	SpeedBoost(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
};