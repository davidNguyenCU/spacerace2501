#pragma once

#include "GameEntity.h"
#include "Window.h"

class Map : public GameEntity {
public:
	Map(glm::vec3 &entityPos, glm::vec3 &entityScale, glm::vec3 &roadScale, float entityRotationAmount, GLuint entityTexture, GLuint roadTex, GLint entityNumElements);

	void update(double deltaTime, glm::vec3 &playerPosition);
	void update(double deltaTime);
	void render(Shader &shader);
	void renderRoad(Shader& shader);

private:
	GLuint roadTexture;
	glm::vec3 roadScale;
};