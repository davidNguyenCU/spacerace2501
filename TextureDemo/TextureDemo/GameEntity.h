#pragma once

#include <../../Libraries/include/GL/glew.h> // window management library
#include <../../Libraries/include/GL/glfw3.h>
#include <../../Libraries/include/glm/glm.hpp>
#include <../../Libraries/include/glm/gtc/matrix_transform.hpp> //

#include "Shader.h"
#include "RenderedObject.h"

#include <vector>

using namespace std;

//Class of all game entities in in the game
class GameEntity {
public:
	GameEntity(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements);

	virtual void update(double deltaTime) = 0;
	void render(Shader &shader);

	inline glm::vec3 getPosition() const { return position; }
	inline void setXposition(float newX) { position.x = newX; }
	inline void setYposition(float newY) { position.y = newY; }
	inline float getRotation() { return rotationAmount; }
protected:
	glm::vec3 position, scale;
	glm::vec3 screenPosition;
	float rotationAmount;

	GLuint texture;
	GLint numElements;

	glm::vec3 tint;
};