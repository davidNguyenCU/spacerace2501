
#include "DynamicGameEntity.h"

DynamicGameEntity::DynamicGameEntity(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), velocity(entityVelocity), acceleration(entityAcceleration)
{
	//velocity = entityVelocity;
	//acceleration = entityAcceleration;
}

void DynamicGameEntity::update(double deltaTime) {
	//forward = glm::normalize(position);
	position += velocity * (float)deltaTime;
	//std::cout << "Updating" << std::endl;
}

void DynamicGameEntity::goFASTER(int yesSPD, double deltaTime) {


	if (yesSPD == 1) {
		acceleration += 0.9 * deltaTime;
	}
	else if (yesSPD == -1) {
		acceleration.y -= 0.9 * deltaTime;
	}
	else if (yesSPD == 0) {
		acceleration.y = 0;
	}
	velocity.y += acceleration.y * (float)deltaTime;
}
