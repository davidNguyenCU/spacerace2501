#pragma once
#include "DynamicGameEntity.h"

class Obstacle : public DynamicGameEntity {

	Obstacle(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

};