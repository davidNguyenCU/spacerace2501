#include "GameEntity.h"
#include "Globals.h"

GameEntity::GameEntity(glm::vec3 &entityPos, glm::vec3 &entityScale, float entityRotationAmount, GLuint entityTexture, GLint entityNumElements)
	: position(entityPos), scale(entityScale), rotationAmount(entityRotationAmount), texture(entityTexture), numElements(entityNumElements)
{
}

void GameEntity::render(Shader &shader) {

	// Do not draw offscreen objects
	if (screenPosition.x < -1.0f || screenPosition.x > 1.0f ||
		screenPosition.y < -1.0f || screenPosition.y > 1.0f) return;

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader 
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), screenPosition);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotationAmount, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("x", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}