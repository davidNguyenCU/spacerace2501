#pragma once

#include "DynamicGameEntity.h"
#include "Player.h"

class Asteroid : public DynamicGameEntity {
public:
	Asteroid(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity);

	virtual void update(double deltaTime) override;

	Player *getPlayer() { return player; };
private:
	Player * player;
};