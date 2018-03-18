#include "Map.h"
#include "Globals.h"
#include <math.h>

Map::Map(glm::vec3 &entityPos, glm::vec3 &entityScale, glm::vec3 &roadScaleIn, float entityRotationAmount, GLuint entityTexture, GLuint roadTex, GLint entityNumElements)
	: GameEntity(entityPos, entityScale, entityRotationAmount, entityTexture, entityNumElements)
{
	roadTexture = roadTex;
	roadScale = roadScaleIn;
}

void Map::update(double deltaTime) {
	std::cout << "Do not use" << std::endl;
}

void Map::update(double deltaTime, glm::vec3 &playerPosition) {
	//position.x = 0.8f * sin(glfwGetTime());
	/*float verticalChunkStartPos = floorf(playerPosition.y);
	
	if (verticalChunkStartPos % 6.0f == 0.0f) {

	}*/
	/*screenPosition.x = position.x - playerPosition.x;
	screenPosition.y = position.y - (int(playerPosition.y) % 6);*/
	position.y = 2 * floor(playerPosition.y / 2.0f);
	screenPosition = position - playerPosition;
	/*float remainder = fmod(screenPosition.y, 6.0f);
	int quotient = (screenPosition.y - remainder) / 6;
	screenPosition.y = fmod()*/
}

void Map::render(Shader &shader) {

	glBindTexture(GL_TEXTURE_2D, texture);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAmount, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), screenPosition);
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	shader.setUniformMat4("x", transformationMatrix);

	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

void Map::renderRoad(Shader &shader) {
	/*
	float x1 = 50.0f;
	float x2 = 100.0f;
	float y1 = 50.0f;
	float y2 = 100.0f;

	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(x1, y1, x2, y2);
	glEnd();
	glFlush();
	*/
	glBindTexture(GL_TEXTURE_2D, roadTexture);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), roadScale);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAmount, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), screenPosition);
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;

	shader.setUniformMat4("x", transformationMatrix);

	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
