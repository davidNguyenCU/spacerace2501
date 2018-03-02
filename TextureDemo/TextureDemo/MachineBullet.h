#pragma once

#include "Bullet.h"

class MachineBullet : public Bullet {
public:
	MachineBullet(glm::vec3 &entityPos, glm::vec3 entityVelocity, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;

private:
	//float speed = 0.002f;
	//glm::vec3 bulletScale = glm::vec3(0.00002f);
};