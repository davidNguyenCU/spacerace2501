#pragma once
#include "Player.h"
#include "Enemy.h"
#include "HUD.h"
#include "RenderedObject.h"
#include "Ship.h"

class GameManager {
public:
	GameManager();
	//GameManager(Shader& shader, int aSize);

	void update(double deltaTime);
	void checkCollisions(Player * player, Enemy * theEnemy);

	void setPlayer(Player * player);
	void setEnemies(Enemy * enemies);
	void addEnemy(Enemy * enemies);
	void setMousePos(float aMouseX, float aMouseY);

	void playerShoot(bool pressingDown, bool holdingDown);

	void setTextures(int texSize, GLuint& mouseTexture, GLuint& bulletTex, GLuint& rocketTex);
	void updateUI();
	void renderAll(Shader& shader);

private:
	const static int MAX_NUM_SHIPS = 10;
	int numShips;

	std::vector<Enemy *> enemies;
	Player * player;
	HUD hud;

	int squareGeometry;

	const glm::vec3 mouseScale = glm::vec3(0.12f);
	GLuint * mouseTexture;

	RenderedObject mousePointerTexture;
	RenderedObject bulletTexture;
	RenderedObject rocketTexture;
	float mouseX, mouseY;

	vector<MachineBullet> bullets;
	vector<RocketBullet> rockets;

	void shootGun(glm::vec3 source, glm::vec3 target);
	void shootRocket(glm::vec3 source, glm::vec3 target);
};
