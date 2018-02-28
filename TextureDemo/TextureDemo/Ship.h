#pragma once

#include "DynamicGameEntity.h"

class Ship : public DynamicGameEntity {
public:
	Ship(glm::vec3 &entityPos, glm::vec3 entityVelocity, glm::vec3 entityAcceleration, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	void update(double deltaTime) override;

	enum GunType
	{
		MachineGun,
		Rocket
	};

	GunType getCurrentGun();
	void shootGun(glm::vec2 target);
	void shootRocket(glm::vec2 target);
	void switchGun();

private:
	GunType currentGun;
	int gunAmmo;
	int rocketAmmo;
};