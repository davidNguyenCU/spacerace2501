#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Shader.h"

class ParticleSystem {
	ParticleSystem();

	void drawParticles(GLuint particleProgram, int particleSize);

private:
	GLuint texture;
};