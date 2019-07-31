#pragma once

#include "DynamicGameEntity.h"
#include "Player.h"

class Blackhole : public DynamicGameEntity {
public:
	Blackhole(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity);

	virtual void update(double deltaTime) override;

	void succ(DynamicGameEntity *succed);

	Player *getPlayer() { return player; };
private:
	Player * player;
};