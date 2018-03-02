#pragma once

#include "Ship.h"
#include "Player.h"

class Enemy : public Ship {
public:
	Enemy(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity);

	virtual void update(double deltaTime) override;

	//setters
	void setPosition(glm::vec3 updatedPosition);
	void setVelocity(glm::vec3 updatedVelocity);
	void setAcceleration(glm::vec3 updatedAcceleration);

	//getters
	glm::vec3 getVelocity() { return velocity; };
	glm::vec3 getAcceleration() { return acceleration; };
	Player *getPlayer() { return player; };


private:
	Player *player;
};