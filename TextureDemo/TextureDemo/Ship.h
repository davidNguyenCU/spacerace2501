#pragma once

#include "DynamicGameEntity.h"
#include "MachineBullet.h"
#include "RocketBullet.h"

class Ship : public DynamicGameEntity {
public:
	Ship(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	float bashStartPosition;
	double timeOfBashStart;
	bool bashStarted;
	bool isBashing;
	bool ableToBashAgain;

	void update(double deltaTime) override;
	void sideMovement(int state, double deltaTime);
	void recordShipBashStart(float startBashPosition, double bashTimeStart);
	bool sideBash(bool bashing, int bashDirection, double deltaTime, double currentTime);
	void checkBashCoolDown(double currentTime);

	enum GunType
	{
		MachineGun,
		Rocket
	};

	GunType getCurrentGun();
	//void shootGun(glm::vec2 target, GLuint texture, int size);
	//void shootRocket(glm::vec2 target, GLuint texture, int size);
	void switchGun();

	void render(Shader& shader);

private:
	GunType currentGun;
	int gunAmmo;
	int rocketAmmo;
	static const int MAX_GUN_AMMO = 1;
	static const int MAX_ROCKET_AMMO = 1;

	float bashVelocity;
	float bashAccler;
};