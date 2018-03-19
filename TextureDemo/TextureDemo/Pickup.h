#pragma once

#include "DynamicGameEntity.h"

class Pickup : public DynamicGameEntity {
public:
	Pickup(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);
	inline void setActiveState(bool state) { active = state; }
	inline bool getActiveState() { return active; }
	void Pickup::update(double deltaTime, glm::vec3 playerPosition);
	void swapActiveState();
	float width, height;
private:
	bool active = true;
};