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

	//inline bool canShootGun() { return (gunAmmo > 0 && gunTimer <= 0.0f); };
	//inline bool canShootRocket() { return (rocketAmmo > 0 && rocketTimer <= 0.0f);  };
	bool canShootGun();
	bool canShootRocket();

	void render(Shader& shader);

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
};