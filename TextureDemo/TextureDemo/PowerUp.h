#pragma once

#include "DynamicGameEntity.h"

enum Type
{
	accelerate,
	refill
};

class PowerUp : public DynamicGameEntity {
public:
	void updatePos(double deltaTime);
	PowerUp(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Type typeOfPowerup);
	Type type;
	float height = 0.1;
	float width = 0.1;
};