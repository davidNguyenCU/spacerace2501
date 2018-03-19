
#include "DynamicGameEntity.h"

DynamicGameEntity::DynamicGameEntity(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements), velocity(entityVelocity), acceleration(entityAcceleration)
{
	//velocity = entityVelocity;
	//acceleration = entityAcceleration;
}

void DynamicGameEntity::update(double deltaTime) {
	//forward = glm::normalize(position);
	//cout << "Updating" << endl;
	//position += velocity * (float)deltaTime;
	//std::cout << "Updating" << std::endl;
	cout << "Do not call" << endl;
}

void DynamicGameEntity::update(double deltaTime, glm::vec3 playerPosition) {
	acceleration = momentum / mass;
	velocity += acceleration;

	//printf("%f", velocity.x);

	position += velocity * (float)deltaTime;
	screenPosition = position - playerPosition;
}

void DynamicGameEntity::updateMomentum(glm::vec3 newMomentum){
	momentum += newMomentum;
}

void DynamicGameEntity::goFASTER(int yesSPD, double deltaTime) {


	if (yesSPD == 1) {
		//acceleration += 1.5 * deltaTime;
		//updateMomentum(glm::vec3(0, 0.00001, 0));
		momentum.y += 0.0001;
	}
	else if (yesSPD == -1) {
		//acceleration.y -= 1.5 * deltaTime;
		//updateMomentum(glm::vec3(0, -0.00001, 0));
		momentum.y -= 0.0001;
	}
	else if (yesSPD == 0) {
		//updateMomentum(glm::vec3(0, 0, 0));
		momentum.y = 0;
	}
}
