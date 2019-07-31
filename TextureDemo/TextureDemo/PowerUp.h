#pragma once

#include "Ship.h"

enum Type
{
	accelerate,
	refill
};

class PowerUp : public Ship {
public:
	//void render(Shader shader);
	void updatePos(double deltaTime);
	PowerUp(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint &turretTex, GLint entityNumElements, Type typeOfPowerup);
	Type type;
	float height = 0.1;
	float width = 0.1;
};