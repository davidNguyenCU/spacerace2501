#pragma once

#include "DynamicGameEntity.h"

class Bullet : public DynamicGameEntity {
public:
	Bullet(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;

private:
	const glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
};