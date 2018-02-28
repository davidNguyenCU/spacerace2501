#include "GameManager.h"

GameManager::GameManager()
{

}

GameManager::GameManager(Shader& aShader, int aSize)
{
	squareGeometry = aSize;
	HUD hud();
}

void GameManager::updateUI() {
	
}

void GameManager::setPlayer(Player * aPlayer) {
	player = aPlayer;
}

void GameManager::setEnemies(Enemy * enemies) {
	enemies = enemies;
}

void GameManager::setMousePos(float aMouseX, float aMouseY)
{
	mouseX = aMouseX;
	mouseY = aMouseY;
}

void GameManager::setTextures(GLuint& mouseTex) {
	mousePointerTexture = RenderedObject(mouseTex);
}

void GameManager::renderAll(Shader& shader) {
	//std::cout << "Mouse: (" << mouseX << "," << mouseY << ")" << std::endl;
	mousePointerTexture.render(glm::vec3(mouseX, mouseY, 0.0f), mouseScale, 0.0f, squareGeometry, shader);
}

void GameManager::playerShoot(bool readyGun, bool readyRocket) {
	Ship::GunType currentGun = player->getCurrentGun();
	glm::vec2 target = glm::vec2(mouseX, mouseY);

	//std::cout << "Pressing down: " << pressingDown << "Holding down" << holdingDown << std::endl;

	if (readyRocket /*&& currentGun == Ship::Rocket*/) {
		player->shootRocket(target);
	}
	else if (readyGun /*&& currentGun == Ship::MachineGun*/) {
		player->shootGun(target);
	}
}