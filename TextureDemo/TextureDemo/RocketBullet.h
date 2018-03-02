#pragma once

#include "Bullet.h"

class RocketBullet : public Bullet {
public:
	RocketBullet(glm::vec3 &entityPos, glm::vec3 entityDirection, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;

private:
	//static float speed = 0.002f;
	//glm::vec3 bulletScale = glm::vec3(0.00002f);
};