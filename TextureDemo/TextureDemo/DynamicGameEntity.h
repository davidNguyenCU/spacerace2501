#pragma once

#include "GameEntity.h"

class DynamicGameEntity : public GameEntity {
public:
	DynamicGameEntity(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
	void update(double deltaTime, glm::vec3 playerPosition);

	void goFASTER(int yesSPD, double deltaTime);

protected:
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 forward;

};