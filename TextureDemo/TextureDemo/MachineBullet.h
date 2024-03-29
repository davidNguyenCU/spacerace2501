#pragma once

#include "Bullet.h"

class MachineBullet : public Bullet {
public:
	MachineBullet(glm::vec3 &entityPos, glm::vec3 entityVelocity, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

private:
	//float speed = 0.2f;
	//glm::vec3 bulletScale = glm::vec3(0.00002f);
};