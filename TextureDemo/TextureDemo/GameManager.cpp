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
	std::cout << "Mouse: (" << mouseX << "," << mouseY << ")" << std::endl;
	mousePointerTexture.render(glm::vec3(mouseX, mouseY, 0.0f), mouseScale, 0.0f, squareGeometry, shader);
}