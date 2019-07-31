#pragma once

#include "Ship.h"
#include "Player.h"

//Subclass of ships, handles enemy ships
class Enemy : public Ship {
public:
	Enemy(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint &turretTex, GLint entityNumElements, Player *playerEntity);

	void update(double deltaTime);
	//setters
	void setPosition(glm::vec3 updatedPosition);
	void setVelocity(glm::vec3 updatedVelocity);
	void setAcceleration(glm::vec3 updatedAcceleration);

	//getters
	Player *getPlayer() { return player; };

private:
	Player *player;
};