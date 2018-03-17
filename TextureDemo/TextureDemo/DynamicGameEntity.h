#pragma once

#include "GameEntity.h"

//YEET
//Subclass, handles all game entities that have some form of (potential) movement 
class DynamicGameEntity : public GameEntity {
public:
	DynamicGameEntity(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
	void update(double deltaTime, glm::vec3 playerPosition);

	void goFASTER(int yesSPD, double deltaTime);

	inline glm::vec3 getAcceleration() { return acceleration; };
	inline glm::vec3 getVelocity() { return velocity; };

protected:
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 forward;

};