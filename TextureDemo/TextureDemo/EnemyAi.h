#pragma once
#include "Enemy.h"

enum Behaviour
{
	stupidChase,
	stupidFlee
};

class EnemyAi {
public:
	EnemyAi(Enemy* controlledEnemy, Behaviour behaviour);
	void update(double deltaTime);
	void flip();
private:
	Enemy* enemy;
	Behaviour behaviourController;
};