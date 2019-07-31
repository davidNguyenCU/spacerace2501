#pragma once

#include "Bullet.h"

class RocketBullet : public Bullet {
public:
	RocketBullet(glm::vec3 &entityPos, glm::vec3 entityDirection, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

private:
	//float speed = 2.0f;
	//glm::vec3 bulletScale = glm::vec3(0.00002f);
};