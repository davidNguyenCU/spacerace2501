#pragma once

#include "GameEntity.h"

class Hazard : public GameEntity {
public:
	Hazard(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
};
