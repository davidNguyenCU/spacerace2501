#include "ParticleSystem.h"

/*---------------------------------------------------------------------------------*/
// draw all particles -- note that the transformation is just hacked in here,
// but you can set it in your own code (e.g., to attach a particle system to
// one of the cars)
/*---------------------------------------------------------------------------------*/
void ParticleSystem::drawParticles(GLuint particleprogram, int particlesize)
{

	// Select proper shader program to use
	glUseProgram(particleprogram);

	//set displacement
	int matrixLocation = glGetUniformLocation(particleprogram, "x");
	int timeLocation = glGetUniformLocation(particleprogram, "time");

	glm::mat4 rot = glm::mat4();
	glm::mat4 world = glm::mat4();

	float k = glfwGetTime();
	//rot = glm::rotate(rot, -k * 360 / 6.283f, glm::vec3(0, 0, 1));
	rot = glm::translate(rot, glm::vec3(0.5, 0, 0));
	rot = glm::scale(rot, glm::vec3(0.1, 0.1, 0.1));
	// get ready to draw, load matrix
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &rot[0][0]);
	glUniform1f(timeLocation, k);
	glBindTexture(GL_TEXTURE_2D, texture);


	/*---------------------------------------------------------------------------------*/
	// Something else you might want to do:
	// - set additive mode for blending (for a fire effect, say)
	// - to do this, call glBlendFunc(GL_ONE,GL_ONE);
	// - and also disable depth writes: glDepthMask(GL_FALSE);
	// - disable depth writes RIGHT BEFORE drawing the particles,
	// - and reenable them afterwards with glDepthMask(GL_TRUE);
	/*---------------------------------------------------------------------------------*/
	//glBlendFunc(GL_ONE, GL_ONE);
	//glDepthMask(GL_FALSE);

	// Draw 
	glDrawElements(GL_TRIANGLES, 6 * particlesize, GL_UNSIGNED_INT, 0);

	/*-----ENABLE / DISABLE-----*/
	//glDepthMask(GL_TRUE);

}