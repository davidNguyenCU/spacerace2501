#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Shader.h"

class RenderedObject {
public:
	RenderedObject();
	RenderedObject(GLuint& aTexture);

	void render(glm::vec3 position, glm::vec3 scale, float rotationAmount, float numElements, Shader& shader);
	
private:
	GLuint * texture;
};
