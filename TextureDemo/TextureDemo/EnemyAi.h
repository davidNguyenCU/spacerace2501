#pragma once
#include "Enemy.h"

enum Behaviour
{
	stupidChase,
	stupidStay,
	pacifistCompetitor
};

class EnemyAi {
public:
	EnemyAi(Enemy* controlledEnemy, Behaviour behaviour);
	void update(double deltaTime);
private:
	Enemy* enemy;
	Behaviour behaviourController;
};