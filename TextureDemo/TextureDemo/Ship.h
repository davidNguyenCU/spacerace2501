#pragma once

#include "GameEntity.h"

class Ship : public GameEntity {
public:
	Ship(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) override;

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
	int gunAmmo, rocketAmmo;
};