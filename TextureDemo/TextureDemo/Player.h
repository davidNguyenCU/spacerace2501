#pragma once

#include "Ship.h"

//Subclass of ship, specifically handles the player ship
class Player : public Ship {
public:
	Player(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);
};