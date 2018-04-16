#include "Blackhole.h"
#include "Enemy.h"

Blackhole::Blackhole(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements, Player *playerEntity)
	: DynamicGameEntity(entityPos, entityVelocity, entityAcceleration, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	player = playerEntity;
	width = 0.1;
	height = 0.1;
	mass = 5;
	type = asteroid;
}

void Blackhole::update(double deltaTime) {
	//DynamicGameEntity::update(deltaTime, player->getPosition);
	//printf("%f", player->getPosition().x);
	screenPosition = position - player->getPosition();
}


void Blackhole::succ(DynamicGameEntity *succed) {

	if (position.y - succed->getPosition().y < 1.0 &&
		position.y - succed->getPosition().y > -1.0 &&
		position.x - succed->getPosition().x < 1.0 &&
		position.x - succed->getPosition().x > -1.0)
	{
		glm::vec3  vectored = glm::normalize(position - succed->getPosition());
		if (succed->getMomentum().y > 20) {
			succed->updateMomentum(vectored*5.5f);
		}
	}

}