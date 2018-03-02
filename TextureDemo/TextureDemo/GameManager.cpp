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
	for (auto& ship : ships) {
		ship->update(deltaTime);
	}

	for (auto& bullet : bullets) {
		bullet.update(deltaTime);
	}

	for (auto& rocket : rockets) {
		rocket.update(deltaTime);
	}

	updateUI();
}

void GameManager::updateUI() {
	
}

void GameManager::setPlayer(Player * aPlayer) {
	player = aPlayer;
	addShip(aPlayer);
}

// TO DO: Change to array of enemies
void GameManager::setEnemies(Enemy * enemy) {
	enemies = enemy;
	addShip(enemy);
}

void GameManager::addShip(Ship * ship) {
	if (numShips >= MAX_NUM_SHIPS) {
		//std::cout << "ShipArrayFullError" << std::endl;
		return;
	}

	ships.push_back(ship);
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
	for (auto &ship : ships) {
		ship->render(shader);
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
	glm::vec3 target = glm::vec3(mouseX, mouseY, 0.0f);

	//std::cout << "Pressing down: " << pressingDown << "Holding down" << holdingDown << std::endl;

	if (readyRocket /*&& currentGun == Ship::Rocket*/) {
		//player->shootRocket(target, rocketTexture.getTexture(), squareGeometry);
		shootRocket((Ship&) player, (Ship&) target);
	}
	else if (readyGun /*&& currentGun == Ship::MachineGun*/) {
		shootGun((Ship&) player, (Ship&) target);
		//player->shootGun(target, bulletTexture.getTexture(), squareGeometry);
	}
}

void GameManager::shootRocket(Ship& source, Ship& target) {
	glm::vec3 direction = glm::normalize(target.getPosition() - source.getPosition());
	rockets.push_back(RocketBullet(/*source.getPosition()*/glm::vec3(0.0f), direction, source.getRotation(), rocketTexture.getTexture(), squareGeometry));
}

void GameManager::shootGun(Ship& source, Ship& target) {
	glm::vec3 direction = glm::normalize(target.getPosition() - source.getPosition());
	
	bullets.push_back(MachineBullet(/*source.getPosition()*/glm::vec3(0.0f), direction, source.getRotation(), rocketTexture.getTexture(), squareGeometry));
}
