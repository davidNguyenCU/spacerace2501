#pragma once

#include <../../Libraries/include/GL/glew.h> // window management library
#include <../../Libraries/include/glm/glm.hpp>
#include <../../Libraries/include/glm/gtc/type_ptr.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ResourceManager.h"

class Shader {
public:
	Shader(const char *vertPath, const char *fragPath);
	~Shader();

	GLuint SetupParticleShaders();

	void enable();
	void disable();

	void setUniform1i(const GLchar *name, int value);
	void setUniform1f(const GLchar *name, float value);
	void setUniform2f(const GLchar *name, const glm::vec2 &vector);
	void setUniform3f(const GLchar *name, const glm::vec3 &vector);
	void setUniform4f(const GLchar *name, const glm::vec4 &vector);
	void setUniformMat4(const GLchar *name, const glm::mat4 &matrix);

	inline GLuint getShaderID() { return shaderProgram; }
private:
	GLuint shaderProgram;
};