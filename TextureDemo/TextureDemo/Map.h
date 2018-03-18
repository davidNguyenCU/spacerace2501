#pragma once

#include "GameEntity.h"
#include "Window.h"

static const float roadWidth = 3.0f / 5.0f;
static const glm::vec3 roadScale = glm::vec3(2.0f * roadWidth, 6.0f, 0.0f);

class Map : public GameEntity {
public:
	Map(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLuint roadTex, GLint entityNumElements);

	void update(double deltaTime, glm::vec3 &playerPosition);
	void update(double deltaTime);
	void render(Shader &shader);
	void renderRoad(Shader& shader);
	static float getRoadWidth() { return roadScale.x; };

private:
	GLuint roadTexture;
};