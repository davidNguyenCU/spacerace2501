#include "RenderedObject.h"

RenderedObject::RenderedObject() 
{
	
}

RenderedObject::RenderedObject(GLuint& aTexture) 
	:texture(&aTexture)
{
}

void RenderedObject::render(glm::vec3 position, glm::vec3 scale, float rotationAmount, float numElements, Shader& shader) {
	//std::cout << "Render" << std::endl;
	glBindTexture(GL_TEXTURE_2D, *texture);

	// Setup the transformation matrix for the shader 
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAmount, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("x", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

GLuint RenderedObject::getTexture() {
	return *texture;
}