#pragma once

#include "EnemyAi.h"

EnemyAi::EnemyAi(Enemy* controlledEnemy, Behaviour behaviour) 
{
	enemy = controlledEnemy;
	behaviourController = behaviour;
}


void EnemyAi::update(double deltaTime) 
{
	if (behaviourController == stupidChase) 
	{
		//What I'm doing here written sanely:
		//glm::vec3 targetv = glm::normalize(TargetPosition - EnemyPosition);
		//acceleration = AccelerationCap * (targetv - EnemyVelocity) / glm::length(targetv - EnemyVelocity);
		enemy->setAcceleration(glm::vec3(0.5f, 0.5f, 0.5f) * (glm::normalize(enemy->getPlayer()->getPosition() - enemy->getPosition()) - enemy->getVelocity()) / glm::length(glm::normalize(enemy->getPlayer()->getPosition() - enemy->getPosition()) - enemy->getVelocity()));
		//std::
		//<< glm::length(glm::normalize(enemy->getPlayer()->getPosition() - enemy->getPosition()) - enemy->getVelocity());
		enemy->setVelocity(enemy->getVelocity() + enemy->getAcceleration() * (float)deltaTime);
	}
	else if (behaviourController == stupidFlee)
	{
	}
	else if (behaviourController == stupidStay) {
		enemy->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void EnemyAi::flip() 
{
	if (behaviourController == stupidChase){ behaviourController = stupidFlee; }
	else if (behaviourController == stupidFlee) { behaviourController = stupidChase; }
}