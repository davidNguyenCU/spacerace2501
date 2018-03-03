#include "GameManager.h"

GameManager::GameManager()
{
	numShips = 0;
}

/*GameManager::GameManager(Shader& aShader, int aSize)
{
	squareGeometry = aSize;
	HUD hud();
}*/

void GameManager::update(double deltaTime) {

	player->update(deltaTime, player->getPosition());

	for (auto& enemy : enemies) {
		enemy->update(deltaTime);
	}

	for (auto& bullet : bullets) {
		bullet.update(deltaTime, player->getPosition());
	}

	for (auto& rocket : rockets) {
		rocket.update(deltaTime, player->getPosition());
	}

	updateUI();
}

void GameManager::updateUI() {
	
}

void GameManager::checkCollisions(Player * player, Enemy * theEnemy) {
	float playerWidth = player->width;
	float playerHeight = player->height;
	float playerXpos = player->getPosition().x;
	float playerYpos = player->getPosition().y;

	float enemyWidth = theEnemy->width;
	float enemyHeight = theEnemy->height;
	float enemyXpos = theEnemy->getPosition().x;
	float enemyYpos = theEnemy->getPosition().y;

	if (playerXpos < enemyXpos + enemyWidth &&
		enemyXpos < playerXpos + playerWidth &&
		playerYpos < enemyYpos + enemyHeight &&
		enemyYpos < playerYpos + playerHeight) {
		
		//printf("COLLIDING");

	}
}

void GameManager::setPlayer(Player * aPlayer) {
	player = aPlayer;
}

// TO DO: Change to array of enemies
void GameManager::setEnemies(Enemy * enemy) {
	addEnemy(enemy);
}

void GameManager::addEnemy(Enemy * enemy) {
	if (numShips >= MAX_NUM_SHIPS) {
		//std::cout << "ShipArrayFullError" << std::endl;
		return;
	}

	enemies.push_back(enemy);
	numShips++;
	//std::cout << ships.size() << std::endl;
}

void GameManager::setMousePos(float aMouseX, float aMouseY)
{
	mouseX = aMouseX;
	mouseY = aMouseY;
}

void GameManager::setTextures(int texSize, GLuint& mouseTex, GLuint& bulletTex, GLuint& rocketTex) {
	squareGeometry = texSize;
	mousePointerTexture = RenderedObject(mouseTex);
	bulletTexture = RenderedObject(bulletTex);
	rocketTexture = RenderedObject(rocketTex);
}

void GameManager::renderAll(Shader& shader) {
	//std::cout << "Mouse: (" << mouseX << "," << mouseY << ")" << std::endl;
	mousePointerTexture.render(glm::vec3(mouseX, mouseY, 0.0f), mouseScale, 0.0f, squareGeometry, shader);

	player->render(shader);

	for (auto &enemy : enemies) {
		enemy->render(shader);
	}

	/*for (auto& bullet : bullets) {
		bullet.render(shader);
	}*/

	for (auto& rocket : rockets) {
		rocket.render(shader);
	}
}

void GameManager::playerShoot(bool readyGun, bool readyRocket) {
	Ship::GunType currentGun = player->getCurrentGun();

	float globalX = player->getPosition().x + mouseX;
	float globalY = player->getPosition().y + mouseY;

	glm::vec3 target = glm::vec3(globalX, globalY, 0.0f);

	//std::cout << "Pressing down: " << pressingDown << "Holding down" << holdingDown << std::endl;

	if (readyRocket /*&& currentGun == Ship::Rocket*/) {
		//player->shootRocket(target, rocketTexture.getTexture(), squareGeometry);
		shootRocket(player->getPosition(), target);
	}
	else if (readyGun /*&& currentGun == Ship::MachineGun*/) {
		shootGun(player->getPosition(), target);
		//player->shootGun(target, bulletTexture.getTexture(), squareGeometry);
	}
}

void GameManager::shootRocket(glm::vec3 source, glm::vec3 target) {

	cout << source.x << ", " << source.y << endl;

	glm::vec3 direction = glm::normalize(target - source);
	cout << direction.x << ", " << direction.y << endl;

	float rotation = 180.0 / 3.14159 * atan2f(direction.y, direction.x);
	rockets.push_back(RocketBullet(/*source.getPosition()*/source, direction, 0.0f, rocketTexture.getTexture(), squareGeometry));
}

void GameManager::shootGun(glm::vec3 source, glm::vec3 target) {

	glm::vec3 direction = glm::normalize(target - source);

	float rotation = 180.0 / 3.14159 * atan2f(direction.y, direction.x);
	
	bullets.push_back(MachineBullet(/*source.getPosition()*/source, direction, rotation, rocketTexture.getTexture(), squareGeometry));
}
