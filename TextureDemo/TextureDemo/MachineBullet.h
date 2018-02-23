#pragma once

#include "Bullet.h"

class MachineBullet : public Bullet {
public:
	MachineBullet(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, glm::vec3 &bulletVelocity);

	virtual void update(double deltaTime) override;
private:
	glm::vec3 velocity;
};