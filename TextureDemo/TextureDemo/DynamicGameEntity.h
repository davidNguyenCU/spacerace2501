#pragma once

#include "GameEntity.h"

//YEET
//Subclass, handles all game entities that have some form of (potential) movement 
class DynamicGameEntity : public GameEntity {
public:
	DynamicGameEntity(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;
	void update(double deltaTime, glm::vec3 playerPosition);
	float mass;

	void goFASTER(int yesSPD, double deltaTime);
	void updateMomentum(glm::vec3 newMomentum);
	void render(Shader& shader);
	float getWidth() { return width; }
	float getHeight() { return height; }
	int getType() { return type;}
	inline void fastASTER() { momentum.y += 1000.0; }
	inline glm::vec3 getAcceleration() { return acceleration; }
	inline glm::vec3 getVelocity() { return velocity; }
	inline glm::vec3 getMomentum() { return momentum; }

protected:
	enum entityType {
		ship,
		asteroid,
		testCase
	};

	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::vec3 forward;
	glm::vec3 momentum;
	float width;
	float height;
	unsigned int type;

};