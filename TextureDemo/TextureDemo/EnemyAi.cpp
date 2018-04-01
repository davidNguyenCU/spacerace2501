#pragma once

#include "EnemyAi.h"

EnemyAi::EnemyAi(Enemy* controlledEnemy, Behaviour behaviour) 
{
	enemy = controlledEnemy;
	behaviourController = behaviour;
}


void EnemyAi::update(double deltaTime) 
{
	float playerWidthHalf = enemy->getPlayer()->getWidth()*0.5f;
	float playerHeightHalf = enemy->getPlayer()->getHeight()*0.5f;
	glm::vec3 enemyPosition = enemy->getPosition();
	glm::vec3 playerPosition = enemy->getPlayer()->getPosition();

	if (behaviourController == stupidChase) 
	{
		//What I'm doing here written sanely:
		//glm::vec3 targetv = glm::normalize(TargetPosition - EnemyPosition);
		//acceleration = AccelerationCap * (targetv - EnemyVelocity) / glm::length(targetv - EnemyVelocity);
		enemy->setAcceleration(glm::vec3(0.5f, 0.5f, 0.0f) * (glm::normalize(enemy->getPlayer()->getPosition() - enemy->getPosition()) - enemy->getVelocity()) / glm::length(glm::normalize(enemy->getPlayer()->getPosition() - enemy->getPosition()) - enemy->getVelocity()));
		//enemy->setAcceleration(momentum / enemy->mass);



		
		//std::
		//<< glm::length(glm::normalize(enemy->getPlayer()->getPosition() - enemy->getPosition()) - enemy->getVelocity());
		enemy->setVelocity(enemy->getVelocity() + enemy->getAcceleration() * (float)deltaTime);
	}
	
	else if (behaviourController == stupidStay) 
	{
		enemy->setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	else if (behaviourController == pacifistCompetitor)
	{
		/*if ((enemyPosition.x < playerPosition.x + playerWidthHalf && enemyPosition.x > playerPosition.x - playerWidthHalf) && enemyPosition.y < playerPosition.y + playerHeightHalf)
		{
			if (playerPosition.x > 0)
			{
				enemy->setAcceleration(glm::vec3(-0.3f, 0.0f, 0.0f));
			}
			else
			{
				enemy->setAcceleration(glm::vec3(0.3f, 0.0f, 0.0f));
			}
		}
		else if (enemyPosition.y > playerPosition.y + playerHeightHalf)
		{
			if (enemyPosition.x > 0.3f)
			{
				enemy->setAcceleration(glm::vec3(-0.3f, 0.0f, 0.0f));
			}
			else if (enemyPosition.x < -0.3f)
			{
				enemy->setAcceleration(glm::vec3(0.3f, 0.0f, 0.0f));
			}
			else if (enemy->getVelocity().x > 0)
			{
				enemy->setAcceleration(glm::vec3(-0.1f, 0.0f, 0.0f));
			}
			else if (enemy->getVelocity().x < 0)
			{
				enemy->setAcceleration(glm::vec3(0.1f, 0.0f, 0.0f));
			}
		}

		if (enemy->getVelocity().y > 0.5)
		{
			enemy->setAcceleration(glm::vec3(enemy->getAcceleration().x, 0.0, 0.0));
		}
		else
		{
			enemy->setAcceleration(glm::vec3(enemy->getAcceleration().x, 0.3, 0.0));
		}
		std::
		<< enemy->getAcceleration().x << std::endl;
		enemy->setVelocity(enemy->getVelocity() + enemy->getAcceleration() * (float)deltaTime * glm::vec3(0.5, 0.5, 0.0));*/

		if (enemyPosition.y < playerPosition.y && enemyPosition.y > playerPosition.y - 0.8f)
		{
			enemy->setAcceleration(glm::vec3(0.0f, 0.2f, 0.0f));
			if (abs(enemyPosition.x - playerPosition.x) < 0.2f)
			{
				if (enemyPosition.x >= playerPosition.x)
				{
					enemy->setVelocity(glm::vec3(0.2f, 0.2f, 0.0f));
				}
				else
				{
					enemy->setAcceleration(glm::vec3(-0.2f, 0.2f, 0.0f));
				}
			}
		}
		else
		{
			if (abs(enemyPosition.x) > 0.1)
			{
				if (enemyPosition.x > 0)
				{
					enemy->setAcceleration(glm::vec3(-0.2f, 0.2f, 0.0f));
				}
				else
				{
					enemy->setAcceleration(glm::vec3(0.2f, 0.2f, 0.0f));
				}
			}
			else
			{
				enemy->setAcceleration(glm::vec3(0.0f, 0.1f, 0.0f));
				glm::vec3 currVel = enemy->getVelocity();
				enemy->setVelocity(glm::vec3(0.0f, currVel.y, 0.0f));
			}
		}

		enemy->setVelocity(enemy->getVelocity() + enemy->getAcceleration() * (float)deltaTime /** glm::vec3(0.5, 0.5, 0.0)*/);
	}

	else if (behaviourController == aggresive)
	{
		/*if ((enemyPosition.x < playerPosition.x + playerWidthHalf && enemyPosition.x > playerPosition.x - playerWidthHalf) && enemyPosition.y < playerPosition.y + playerHeightHalf)
		{
			if (playerPosition.x > 0)
			{
				enemy->setAcceleration(glm::vec3(-0.3f, 0.0f, 0.0f));
			}
			else
			{
				enemy->setAcceleration(glm::vec3(0.3f, 0.0f, 0.0f));
			}
		}*/
		if (abs(enemyPosition.y - playerPosition.y) < 0.2)
		{
			enemy->setAcceleration(glm::normalize(playerPosition - enemyPosition) * 0.4f);
		}
		else
		{
			enemy->setAcceleration(glm::vec3(0.0f, 0.2f, 0.0f));
		}

		enemy->setVelocity(enemy->getVelocity() + enemy->getAcceleration() * (float)deltaTime /** glm::vec3(0.5, 0.5, 0.0)*/);
	}
}