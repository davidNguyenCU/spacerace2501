#pragma once
#include "Player.h"
#include "Enemy.h"
#include "HUD.h"
#include "RenderedObject.h"

class GameManager {
public:
	GameManager();
	GameManager(Shader& shader, int aSize);

	void setPlayer(Player * player);
	void setEnemies(Enemy * enemies);
	void setMousePos(float aMouseX, float aMouseY);
	void setTextures(GLuint& mouseTexture);

	void updateUI();

	void renderAll(Shader& shader);

private:
	Player * player;
	Enemy * enemies;
	HUD hud;

	int squareGeometry;

	const glm::vec3 mouseScale = glm::vec3(0.12f, 0.12f, 0.12f);
	GLuint * mouseTexture;

	RenderedObject mousePointerTexture;
	float mouseX, mouseY;
};
