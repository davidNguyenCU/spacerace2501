#pragma once

#include "Ship.h"
#include "Player.h"

class Enemy : public Ship {
public:
	Enemy(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity);

	virtual void update(double deltaTime) override;
private:
	Player *player;
};