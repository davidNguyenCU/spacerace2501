#pragma once

#include "DynamicGameEntity.h"
#include "MachineBullet.h"
#include "RocketBullet.h"

//Subclass of dynamic (moving) game entity, includes all spawned ships in the game
class Ship : public DynamicGameEntity {
public:
	Ship(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	float bashStartPosition;
	double timeOfBashStart;
	bool bashStarted;
	bool isBashing;
	bool bashCooldown;
	int bashDirection;

	float sideVelocity;
	float width;
	float height;

	void update(double deltaTime, glm::vec3 playerPosition);
	void sideMovement(int state, double deltaTime);
	void sideBash(int state, double currentTime, double deltaTime);

	void hasShotGun();
	void hasShotRocket();

	bool canShootGun();
	bool canShootRocket();

	//void render(Shader& shader);

	float getHealth() { return health;  };

private:

	const float gunCooldown = 5.0f;
	const float rocketCooldown = 10000.0f;

	float gunTimer;
	float rocketTimer;

	void updateBulletTimers(double deltaTime);

	int gunAmmo;
	int rocketAmmo;
	static const int MAX_GUN_AMMO = 10;
	static const int MAX_ROCKET_AMMO = 10;

	static const int MAX_FORWARD_VELOCITY = 2.0f;
	static const int MAX_FORWARD_ACCELERATION = 0.5f;

	static const int MAX_SIDE_VELOCITY = 2.5f;

	float bashVelocity;
	float bashAccler;

	const float MAX_HEALTH = 100.0f;
	float health;
	void outOfBounds(double deltaTime);
	bool isOutOfBounds();
	const float asteroidDamagePerSecond = 10.0f;
};