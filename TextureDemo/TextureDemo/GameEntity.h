#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Shader.h"
#include "RenderedObject.h"

#include <vector>

using namespace std;

class GameEntity {
public:
	GameEntity(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) = 0;
	void render(Shader &shader);

	inline glm::vec3 getPosition() { return position; }
	inline float getRotation() { return rotationAmount; }
protected:
	glm::vec3 position, scale;
	float rotationAmount;

	GLuint texture;
	GLint numElements;
};