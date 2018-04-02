#pragma once

#include "DynamicGameEntity.h"
#include "MachineBullet.h"
#include "RocketBullet.h"


//Subclass of dynamic (moving) game entity, includes all spawned ships in the game
class Ship : public DynamicGameEntity {
public:
	Ship(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint &turretTex, GLint entityNumElements);

	float bashStartPosition;
	double timeOfBashStart;
	bool bashStarted;
	bool isBashing;
	bool bashCooldown;
	int bashDirection;
	int dashType;


	float sideVelocity;

	void update(double deltaTime, glm::vec3 playerPosition);
	void render(Shader &shader);

	void sideMovement(int state, double deltaTime);
	void sideBash(int state, double currentTime, double deltaTime);

	void hasShotGun();
	void hasShotRocket();

	bool canShootGun();
	bool canShootRocket();

	//void render(Shader& shader);

	double getHealth() { return health;  };

	void setTurret(glm::vec3 aimingAt);

	float turretRot;

	static const float MAX_FORWARD_VELOCITY;
	static const float MAX_FORWARD_ACCELERATION;

	static const float MAX_SIDE_VELOCITY;
	static const float MAX_SIDE_ACCELERATION;

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

	float bashVelocity;
	float bashAccler;

	const double MAX_HEALTH = 100.0;
	float health;
	void outOfBounds(double deltaTime);
	bool isOutOfBounds();
	//const double asteroidDamagePerSecond = 1000000000.0;

	RenderedObject turretSprite;
};