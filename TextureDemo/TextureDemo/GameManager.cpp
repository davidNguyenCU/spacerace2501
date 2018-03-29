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

	glm::vec3 mousePos = glm::vec3(mouseX, mouseY, 0.0f);

	player->update(deltaTime, mousePos);

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

void GameManager::checkCollisions(DynamicGameEntity * colliding, DynamicGameEntity * collided) {
	float playerWidth = colliding->getWidth();
	float playerHeight = colliding->getHeight();
	float playerXpos = colliding->getPosition().x;
	float playerYpos = colliding->getPosition().y;

	float enemyWidth = collided->getWidth();
	float enemyHeight = collided->getHeight();
	float enemyXpos = collided->getPosition().x;
	float enemyYpos = collided->getPosition().y;

	if (playerXpos < enemyXpos + enemyWidth &&
		enemyXpos < playerXpos + playerWidth &&
		playerYpos < enemyYpos + enemyHeight &&
		enemyYpos < playerYpos + playerHeight) {

		float xBound = 0;
		float yBound = 0;
		
		if (playerXpos < enemyXpos) {
			colliding->setXposition(playerXpos-0.015);

			if(collided->getType() == 0)
				collided->setXposition(enemyXpos+0.015);

			xBound = playerXpos + playerWidth - enemyXpos;
		}
		if (enemyXpos < playerXpos) {
			colliding->setXposition(playerXpos + 0.015);

			if (collided->getType() == 0)
				collided->setXposition(enemyXpos-0.015);

			xBound = enemyXpos + enemyWidth - playerXpos;
		}
		
		if (enemyYpos < playerYpos) {
			colliding->setXposition(playerXpos + 0.015);

			if (collided->getType() == 0)
				collided->setYposition(enemyYpos - 0.015);

			yBound = enemyYpos + enemyHeight - playerYpos;
		}
		if (playerYpos < enemyYpos) {
			colliding->setYposition(playerYpos - 0.015);

			if (collided->getType() == 0)
				collided->setYposition(enemyYpos + 0.015);

			yBound = playerYpos + playerHeight - enemyYpos;
		}

		if (xBound > yBound || yBound > xBound) {
			glm::vec3 deltaVelocity = colliding->getVelocity() - collided->getVelocity();
			glm::vec3 collisionNormal = glm::normalize(colliding->getPosition() - collided->getPosition());
			float invSumMasses = (1 / colliding->mass) + (1 / collided->mass);

			float CO_OF_RESTITUTION = 0.95;

			float force = -(1 + CO_OF_RESTITUTION) * glm::dot(collisionNormal, deltaVelocity) / invSumMasses; \

				colliding->updateMomentum(force * collisionNormal);
			collided->updateMomentum(-force * collisionNormal);
		}
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
	//Ship::GunType currentGun = player->getCurrentGun();

	//cout << "READY ROCKET" << readyRocket << endl;

	float globalX = player->getPosition().x + mouseX;
	float globalY = player->getPosition().y + mouseY;

	glm::vec3 target = glm::vec3(globalX, globalY, 0.0f);

	//std::cout << "Pressing down: " << pressingDown << "Holding down" << holdingDown << std::endl;

	if (readyRocket /*&& currentGun == Ship::Rocket*/) {
		//player->shootRocket(target, rocketTexture.getTexture(), squareGeometry);
		if (player->canShootRocket()) {
			shootRocket(player->getPosition(), target);
			player->hasShotRocket();
		}
	}
	
	if (readyGun /*&& currentGun == Ship::MachineGun*/) {
		if (player->canShootGun()) {
			shootGun(player->getPosition(), target);
			player->hasShotGun();
		}
		//player->shootGun(target, bulletTexture.getTexture(), squareGeometry);
	}
}

void GameManager::shootRocket(glm::vec3 source, glm::vec3 target) {

	glm::vec3 direction = glm::normalize(target - source);

	float rotation = 180.0 / 3.14159 * atan2f(direction.y, direction.x);
	rockets.push_back(RocketBullet(/*source.getPosition()*/source, direction, 0.0f, rocketTexture.getTexture(), squareGeometry));
}

void GameManager::shootGun(glm::vec3 source, glm::vec3 target) {

	glm::vec3 direction = glm::normalize(target - source);

	float rotation = 180.0 / 3.14159 * atan2f(direction.y, direction.x);
	
	bullets.push_back(MachineBullet(/*source.getPosition()*/source, direction, 0.0f, bulletTexture.getTexture(), squareGeometry));
}
