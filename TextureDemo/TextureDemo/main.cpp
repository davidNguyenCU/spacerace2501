#include <iostream>
#include <stdexcept>
#include <string>
#define GLEW_STATIC
#include <../../Libraries/include/GL/glew.h> // window management library
#include <../../Libraries/include/GL/glfw3.h>
#include <../../Libraries/include/glm/glm.hpp>
#include <../../Libraries/include/glm/gtc/matrix_transform.hpp> //
#include <../../Libraries/include/SOIL/SOIL.h> // read image file
#include <chrono>
#include <thread>

#include "Shader.h"
#include "Window.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "HUD.h"
#include "GameManager.h"
#include "EnemyAi.h"
#include "Map.h"
#include "ObstacleMap.h"
#include "ResourceManager.h"
#include "PowerUp.h"
#include "Blackhole.h"

// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Space Race Prototype 0.1";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.2);

static const int numTexs = 16;
unsigned int game_state = 0;

// Global texture info
GLuint tex[numTexs];

// Input bools
bool PRESSING_FORWARD;
bool PRESSING_BACK;
bool PRESSING_BASH_R;
bool PRESSING_BASH_L;

/*bool PRESSING_SHOOT_GUN_DOWN;
bool PRESSING_SHOOT_GUN_HOLD;*/

bool PRESSING_SHOOT_GUN;
bool PRESSING_SHOOT_ROCKET;
bool PRESSING_SWITCH_WEAPONS;

//State variables for directional movement
int PLAYER_ACCELERATION = 0;
int PLAYER_LEFT_RIGHT = 0;
int BASH_LEFT_RIGHT = 0;

// Create the geometry for a square (with two triangles)
// Return the number of array elements that form the square
int CreateSquare(void) {
	// The face of the square is defined by four vertices and two triangles

	// Number of attributes for vertices and faces
//	const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[]  = {
		//  square (two triangles)
		   //  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	// Return number of elements in array buffer (6 in this case)
	return sizeof(face) / sizeof(GLuint);
}

/*---------------------------------------------------------------------------------*/
// Creates the particle data -- note data layout and initialization
// Each particle has four vertices (same as Square) and attributes -- direction,
// aka velocity, and "time" (a per-particle random phase constant) -- set on a
// per-particle basis
//
// Current initialization puts the velocities into a narrow angular band,
// but you can easily modify it to get a circle, or change it completely
// if you want something totally different
//
/*---------------------------------------------------------------------------------*/
/*
int CreateParticleArray(void) {

	// Each particle is a square with four vertices and two triangles

	// Number of attributes for vertices and faces
	const int vertex_attr = 7;  // 7 attributes per vertex: 2D (or 3D)
	//position(2), direction(2), 2D texture coordinates(2), time(1)
		//   const int face_att = 3; // Vertex indices (3)

		GLfloat vertex[] = {
		//  square (two triangles)
		//  Position      Color             Texcoords
		-0.5f, 0.5f,   1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,   	     0.0f, 1.0f, 0.0f,	      1.0f, 0.0f, // Top-right
		0.5f, -0.5f,    0.0f, 0.0f, 1.0f,	      	    1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	    	  0.0f, 1.0f  // Bottom-left
	};

	GLfloat particleatt[1000 * vertex_attr];
	float theta, r, tmod;

	for (int i = 0; i < 1000; i++)
	{
		if (i % 4 == 0)
		{
			theta = (2 * (rand() % 10000) / 10000.0f - 1.0f)*0.13f;
			r = 0.7f + 0.3*(rand() % 10000) / 10000.0f;
			tmod = (rand() % 10000) / 10000.0f;
		}

		particleatt[i*vertex_attr + 0] = vertex[(i % 4) * 7 + 0];
		particleatt[i*vertex_attr + 1] = vertex[(i % 4) * 7 + 1];

		particleatt[i*vertex_attr + 2] = sin(theta)*r;
		particleatt[i*vertex_attr + 3] = cos(theta)*r;


		particleatt[i*vertex_attr + 4] = tmod;

		particleatt[i*vertex_attr + 5] = vertex[(i % 4) * 7 + 5];
		particleatt[i*vertex_attr + 6] = vertex[(i % 4) * 7 + 6];


	}
	

	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint manyface[1000 * 6];

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 6; j++)
			manyface[i * 6 + j] = face[j] + i * 4;
	}

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleatt), particleatt,
		GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(manyface), manyface,
		GL_STATIC_DRAW);

	// Return number of elements in array buffer
	return sizeof(manyface);
}*/



void setthisTexture(GLuint w, char *fname)
{
	glBindTexture(GL_TEXTURE_2D, w);

	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void setallTexture(void)
{
	//tex = new GLuint[6];
	glGenTextures(numTexs, tex);
	setthisTexture(tex[0], "blueships1.png");
	setthisTexture(tex[1], "orb.png");
	setthisTexture(tex[2], "saw.png");
	setthisTexture(tex[3], "crosshairs.png");
	setthisTexture(tex[4], "bullet.png");
	setthisTexture(tex[5], "rocket.png");
	setthisTexture(tex[6], "map.png");
	setthisTexture(tex[7], "road.png");
	setthisTexture(tex[8], "gameover.png");
	setthisTexture(tex[9], "asteroid.png");
	setthisTexture(tex[10], "turret.png");
	setthisTexture(tex[11], "youWin.png");
	setthisTexture(tex[12], "titlescreen2.png");
	setthisTexture(tex[13], "fire.png");
	setthisTexture(tex[14], "healthBar.png");
	setthisTexture(tex[15], "bhole.png");

	


	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glBindTexture(GL_TEXTURE_2D, tex[6]);
	glBindTexture(GL_TEXTURE_2D, tex[7]);
	glBindTexture(GL_TEXTURE_2D, tex[8]);
	glBindTexture(GL_TEXTURE_2D, tex[9]);
	glBindTexture(GL_TEXTURE_2D, tex[10]);
	glBindTexture(GL_TEXTURE_2D, tex[11]);
	glBindTexture(GL_TEXTURE_2D, tex[12]);
	glBindTexture(GL_TEXTURE_2D, tex[13]);
	glBindTexture(GL_TEXTURE_2D, tex[14]);
	glBindTexture(GL_TEXTURE_2D, tex[15]);
}

/*---------------------------------------------------------------------------------*/
// A setup function for the particle shader program
// Note, you have something like this already for the regular sprites --
// YOU NEED BOTH, this is not a replacement.
/*---------------------------------------------------------------------------------*/
GLuint SetupParticleShaders() // returns ID of newly created program
{

	// Set up shaders
	std::string vp = ResourceManager::LoadTextFile("particleShader.vert");
	const char *source_vpart = vp.c_str();
	std::string fp = ResourceManager::LoadTextFile("shader.frag");
	const char *source_fp = fp.c_str();

	// Create a shader from vertex program source code
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &source_vpart, NULL);
	glCompileShader(vs);

	// Check if shader compiled successfully
	GLint status;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(vs, 512, NULL, buffer);
		throw(std::ios_base::failure(std::string("Error compiling vertex shader:") + std::string(buffer)));
	}

	// Create a shader from the fragment program source code
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &source_fp, NULL);
	glCompileShader(fs);

	// Check if shader compiled successfully
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(fs, 512, NULL, buffer);
		throw(std::ios_base::failure(std::string("Error compiling fragmentshader: ") + std::string(buffer)));
	}

	// Create a shader program linking both vertex and fragment shaders
	// together
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// Check if shaders were linked successfully
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char buffer[512];
		glGetShaderInfoLog(program, 512, NULL, buffer);
		throw(std::ios_base::failure(std::string("Error linking shaders: ") +
			std::string(buffer)));
	}

	// Delete memory used by shaders, since they were already compiled
	// and linked
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;


}


void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	// Quit the program when pressing 'q'
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	PRESSING_FORWARD = (key == GLFW_KEY_W && action == GLFW_PRESS);
	PRESSING_BACK = (key == GLFW_KEY_S && action == GLFW_PRESS);
	PRESSING_BASH_R = (key == GLFW_KEY_D && action == GLFW_PRESS);
	PRESSING_BASH_L = (key == GLFW_KEY_A && action == GLFW_PRESS);

}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
	PRESSING_SHOOT_GUN = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
	PRESSING_SHOOT_ROCKET = (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);
}


// Particle system vertex shader
// DOES NOT REPLACE OLD VERTEX SHADER -- you will want both
//
// This version produces a parabolic trajectory (used for water fountain)
//
/*const char *source_vpart = "#version 130\n\
\n\
// Vertex buffer\n\
in vec2 vertex;\n\
in vec2 dir;\n\
in float t;\n\
in vec2 uv;\n\
out vec2 uv_interp;\n\
\n\
// Uniform (global) buffer\n\
uniform mat4 x;\n\
uniform float time;\n\
\n\
// Attributes forwarded to the fragment shader\n\
out vec4 color_interp;\n\
\n\
\n\
void main()\n\
{\n\
	vec4 ppos;\n\
	float acttime;\n\
	float speed = 14.0;\n\
	float gravity = -9.8;\n\
	acttime = mod(time + t*10, 10.0);\n\
//acttime = mod(time,10);\n\
  ppos = vec4(vertex.x+dir.x*acttime*speed , vertex.y+dir.y*acttime*speed + 0.5*gravity*acttime*acttime, 0.0, 1.0);\n\
    gl_Position = x*ppos;\n\
    \n\
    color_interp = vec4(uv,0.5, 1.0);\n\
    uv_interp = uv;\n\
}";
*/



/*---------------------------------------------------------------------------------*/
// A setup function for the particle shader program
// Note, you have something like this already for the regular sprites --
// YOU NEED BOTH, this is not a replacement.
/*---------------------------------------------------------------------------------*/
/*
}*/

/*---------------------------------------------------------------------------------*/
// Attribute binding for the current program -- note that the vertex data layout
// has changed; I changed it for all vertices (including regular sprites)
// because I was not using the color attribute, but if you are, you will need
// to further change the layout or create a second layout and switch between them
/*---------------------------------------------------------------------------------*/
void AttributeBinding(GLuint program)
{

	// Set attributes for shaders
	// Should be consistent with how we created the buffers for the particle elements
	GLint vertex_att = glGetAttribLocation(program, "vertex");
	glVertexAttribPointer(vertex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(vertex_att);

	GLint dir_att = glGetAttribLocation(program, "dir");
	glVertexAttribPointer(dir_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(dir_att);

	GLint time_att = glGetAttribLocation(program, "t");
	glVertexAttribPointer(time_att, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(4 * sizeof(GLfloat)));
	glEnableVertexAttribArray(time_att);

	GLint tex_att = glGetAttribLocation(program, "uv");
	glVertexAttribPointer(tex_att, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void *)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(tex_att);

}

/*---------------------------------------------------------------------------------*/
// Creates the particle data -- note data layout and initialization
// Each particle has four vertices (same as Square) and attributes -- direction,
// aka velocity, and "time" (a per-particle random phase constant) -- set on a
// per-particle basis
//
// Current initialization puts the velocities into a narrow angular band,
// but you can easily modify it to get a circle, or change it completely
// if you want something totally different
//
/*---------------------------------------------------------------------------------*/
int CreateParticleArray(void) {

	// Each particle is a square with four vertices and two triangles

	// Number of attributes for vertices and faces
	const int vertex_attr = 7;  // 7 attributes per vertex: 2D (or 3D)'

	//position(2), direction(2), 2D texture coordinates(2), time(1)

		//   const int face_att = 3; // Vertex indices (3)


		GLfloat vertex[] = {
		//  square (two triangles)
		//  Position      Color             Texcoords
		-0.5f,  0.5f,		1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f,  0.5f,  	0.0f, 1.0f, 0.0f,	  1.0f, 0.0f, // Top-right
		0.5f, -0.5f,   0.0f, 0.0f, 1.0f,	  1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f  // Bottom-left
	};

	GLfloat particleatt[1000 * vertex_attr];
	float theta, r, tmod;

	for (int i = 0; i < 1000; i++)
	{
		if (i % 4 == 0) {
			theta = (2 * (rand() % 10000) / 10000.0f - 1.0f)*0.13f;
			r = 0.7f + 0.3*(rand() % 10000) / 10000.0f;
			tmod = (rand() % 10000) / 10000.0f;
		}

		particleatt[i*vertex_attr + 0] = vertex[(i % 4) * 7 + 0];
		particleatt[i*vertex_attr + 1] = vertex[(i % 4) * 7 + 1];

		particleatt[i*vertex_attr + 2] = sin(theta)*r;
		particleatt[i*vertex_attr + 3] = cos(theta)*r;


		particleatt[i*vertex_attr + 4] = tmod;

		particleatt[i*vertex_attr + 5] = vertex[(i % 4) * 7 + 5];
		particleatt[i*vertex_attr + 6] = vertex[(i % 4) * 7 + 6];
	}
	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint manyface[1000 * 6];

	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			manyface[i * 6 + j] = face[j] + i * 4;
		}
	}

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleatt), particleatt, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(manyface), manyface, GL_STATIC_DRAW);

	// Return number of elements in array buffer
	return sizeof(manyface);

}
/*---------------------------------------------------------------------------------*/
// draw all particles -- note that the transformation is just hacked in here,
// but you can set it in your own code (e.g., to attach a particle system to
// one of the cars)
/*---------------------------------------------------------------------------------*/
void drawParticles(GLuint particleprogram, glm::vec3 position, int particlesize)
{

	// Select proper shader program to use
	glUseProgram(particleprogram);

	//set displacement
	int matrixLocation = glGetUniformLocation(particleprogram, "x");
	int timeLocation = glGetUniformLocation(particleprogram, "time");

	glm::mat4 rot = glm::mat4();
	glm::mat4 world = glm::mat4();

	float k = glfwGetTime();
	rot = glm::rotate(rot, 180.0f, glm::vec3(0,0,1));
	rot = glm::translate(rot, position);
	rot = glm::scale(rot, glm::vec3(0.05, 0.05, 0.05));
	// get ready to draw, load matrix
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &rot[0][0]);
	glUniform1f(timeLocation, k);
	glBindTexture(GL_TEXTURE_2D, tex[13]);

	// Draw 
	glDrawElements(GL_TRIANGLES, 6 * particlesize, GL_UNSIGNED_INT, 0);

}

void drawExplParticles(GLuint particleprogram, glm::vec3 position, int particlesize) {

	glUseProgram(particleprogram);
	int matrixLocation = glGetUniformLocation(particleprogram, "x");
	int timeLocation = glGetUniformLocation(particleprogram, "time");

	glm::mat4 rot = glm::mat4();
	glm::mat4 world = glm::mat4();


	rot = glm::translate(rot, position);
	rot = glm::scale(rot, glm::vec3(0.02, 0.02, 0.02));

	// get ready to draw, load matrix
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &rot[0][0]);
	glUniform1f(timeLocation, glfwGetTime());
	glBindTexture(GL_TEXTURE_2D, tex[13]);
	glDrawElements(GL_TRIANGLES, 6 * particlesize, GL_UNSIGNED_INT, 0);
}

/*---------------------------------------------------------------------------------*/
// Something else you might want to do:
// - set additive mode for blending (for a fire effect, say)
// - to do this, call glBlendFunc(GL_ONE,GL_ONE);
// - and also disable depth writes: glDepthMask(GL_FALSE);
// - disable depth writes RIGHT BEFORE drawing the particles,
// - and reenable them afterwards with glDepthMask(GL_TRUE);
/*---------------------------------------------------------------------------------*/
//glBlendFunc(GL_ONE, GL_ONE); CODE BEEN PLACED IN MAIN LOOP

/*---------------------------------------------------------------------------------*/
// Couple other basic things:
//
// Create two shader programs, one for regular objects and one for the particle system
// (they can share a fragment shader, although they don't have to)
//
// Make sure you are using the proper shader for your objects;
// compile the shader programs once only, and save the program ID
// so you can later call glUseProgram(correctProgramID);
// after setting the program, subsequent draw calls will use that
// shader set
//
// Create the square and particle set using the supplied functions
// before trying to draw anything
//
// The old vertex shader program is out of synch with the new vertex data layout --
// rewrite the header like so:
// ----
// Source code of vertex shader
const char *source_vp = "#version 130\n\
\n\
// Vertex buffer\n\
in vec2 vertex;\n\
in vec2 dir;\n\
in float t;\n\
in vec2 uv;\n\
out vec2 uv_interp;\n\
\n\
/*---------------------------------------------------------------------------------*/";


// Main function that builds and runs the game
int main(void){
    try {
		// Setup window
		Window window(window_width_g, window_height_g, window_title_g);

        // Set up z-buffer for rendering
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

		// Enable Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create geometry of the square
		int size = CreateSquare();

		// Create particle geometry
		int particleSize = CreateParticleArray();

        // Set up shaders
		Shader shader("shader.vert", "shader.frag"); 
		Shader particleShader("particleShader.vert", "shader.frag");
		Shader explosionShader("shaderExplosion.vert", "shaderExplosion.frag");
		//AttributeBinding(SetupParticleShaders());
		//Shader tintShader("shader.vert", "tintShader.frag");

		// Set event callbacks
		glfwSetKeyCallback(window.getWindow(), KeyCallback);
		glfwSetMouseButtonCallback(window.getWindow(), mouseButtonCallback);
		//glfwSetFramebufferSizeCallback(window.getWindow(), ResizeCallback);

		setallTexture();


		// Disable cursor
		glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Setup game objects

		//GameManager * gameManager = new GameManager();
		GameManager gameManager = GameManager::GameManager();
		gameManager.setTextures(size, tex[3], tex[2], tex[2]);

		Player player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 90.0f, tex[0], tex[10], size);
		Enemy enemy1(glm::vec3(0.2f, -0.6f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], tex[10], size, &player);
		Enemy enemy2(glm::vec3(-0.0f, -0.6f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], tex[10], size, &player);
		EnemyAi enemyaitest(&enemy1, pacifistCompetitor);
		EnemyAi aggresiveEnemy(&enemy2, aggresive);
		//PowerUp powerup(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 90.0f, tex[10], size, accelerate);
		Blackhole bhole(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[15], size, &player);
		PowerUp powerup(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 90.0f, tex[9], tex[1], size, accelerate);


		/*Asteroid aster1(glm::vec3(-0.25f, 1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player);
=======
		Enemy enemy(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], tex[10], size, &player);
		EnemyAi enemyaitest(&enemy, pacifistCompetitor);
		Asteroid aster1(glm::vec3(-0.25f, 1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player);
>>>>>>> 88b956d8b63b923b59b6ef6ee31e171880614d4f
		Asteroid aster2(glm::vec3(0.35f, 1.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player);
		Asteroid aster3(glm::vec3(0.0f, 0.75f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player);
		Asteroid aster4(glm::vec3(-0.2f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player);
		Asteroid aster5(glm::vec3(-0.4f, 0.85f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player);
		Asteroid aster6(glm::vec3(0.0f, 2.05f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player);*/

		Enemy enemies[] = { enemy1, enemy2 };

		//DynamicGameEntity * things[3];

		vector <Asteroid*> asteroids;
		vector <DynamicGameEntity*> physicsObjects;
		physicsObjects.push_back(&player);
		physicsObjects.push_back(&enemy1);
		physicsObjects.push_back(&enemy2);

		ObstacleMap map1(ResourceManager::LoadTextFile("Maps/Map1.txt"));

		for (int i = 0; i < 2; i++)
		{
			asteroids.push_back(new Asteroid(map1.getObstaclePos(i), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 0.0f, tex[9], size, &player));
			//std::cout << asteroids.at(i)->getPosition().x << asteroids.at(i)->getPosition().y;
		}

		physicsObjects.insert(std::end(physicsObjects), std::begin(asteroids), std::end(asteroids));
		/*physicsObjects.push_back(&aster1);
		physicsObjects.push_back(&aster2);
		physicsObjects.push_back(&aster3);
		physicsObjects.push_back(&aster4);
		physicsObjects.push_back(&aster5);
		physicsObjects.push_back(&aster6);*/

		//printf("%d",physicsObjects[0]);
		
		gameManager.setPlayer(&player);
		gameManager.setEnemies(enemies);
		gameManager.addPowerups(&powerup);

		Map map(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(6.0f, 6.0f, 2.0f), 0, tex[6], tex[7], size);

		//Key press states based on pressing and releasing with glfwGetKey
		int CHANGE_GAMESTATE;

		enum gameStateType
		{
			titlescreen,
			game
		};

		int GO_FORWARD;
		int GO_BACKWARD;
		int GO_LEFT;
		int GO_RIGHT;
		int BASH_RIGHT;
		int BASH_LEFT;

		RenderedObject gameOverScreen(tex[8]);
		RenderedObject youWinScreen(tex[11]);
		RenderedObject titleScreen(tex[12]);
		RenderedObject healthBar(tex[14]);
		RenderedObject selectBar1(tex[14]);
		RenderedObject selectBar2(tex[14]);

        // Run the main loop
        bool animating = 1;
		double lastTime = glfwGetTime();
        while (!glfwWindowShouldClose(window.getWindow())){
            // Clear background
			window.clear(viewport_background_color_g);

            // Select proper shader program to use
			shader.enable();

			// Update time
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// KEY PRESS/RELEASE HANDLING
			CHANGE_GAMESTATE = glfwGetKey(window.getWindow(), GLFW_KEY_SPACE);

			GO_FORWARD = glfwGetKey(window.getWindow(), GLFW_KEY_W);
			GO_BACKWARD = glfwGetKey(window.getWindow(), GLFW_KEY_S);
			GO_LEFT = glfwGetKey(window.getWindow(), GLFW_KEY_A);
			GO_RIGHT = glfwGetKey(window.getWindow(), GLFW_KEY_D);
			BASH_RIGHT = glfwGetKey(window.getWindow(), GLFW_KEY_E);
			BASH_LEFT = glfwGetKey(window.getWindow(), GLFW_KEY_Q);

			// Get mouse input for turret
			double mouseX, mouseY;
			glfwGetCursorPos(window.getWindow(), &mouseX, &mouseY);
			float screenSpaceMouseX = (mouseX / window_width_g) * 2 - 1;
			float screenSpaceMouseY = -((mouseY / window_height_g) * 2 - 1);
			gameManager.setMousePos(screenSpaceMouseX, screenSpaceMouseY);

			if (CHANGE_GAMESTATE == 1) {
				game_state=game;
			}

			if (game_state == titlescreen) {
				if (player.mass == 25.0f) {
					selectBar1.render(glm::vec3(-0.8f, -0.06f, 0.0f), glm::vec3(0.16f, 0.21f, 1.0f), 0.0f, size, shader);
				}
				else if (player.mass == 50.0f) {
					selectBar1.render(glm::vec3(-0.8f, -0.325f, 0.0f), glm::vec3(0.16f, 0.21f, 1.0f), 0.0f, size, shader);
				}
				else if (player.mass == 100.0f) {
					selectBar1.render(glm::vec3(-0.8f, -0.58f, 0.0f), glm::vec3(0.16f, 0.21f, 1.0f), 0.0f, size, shader);
				}

				if (player.dashType == 1) {
					selectBar2.render(glm::vec3(0.398f, -0.48f, 0.0f), glm::vec3(0.19f, 0.22f, 1.0f), 0.0f, size, shader);
				}
				else {
					selectBar2.render(glm::vec3(0.398f, -0.18f, 0.0f), glm::vec3(0.19f, 0.22f, 1.0f), 0.0f, size, shader);
				}

				titleScreen.render(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 0.0f, size, shader);

				if (glfwGetKey(window.getWindow(), GLFW_KEY_S)) {
					printf("Smol Mass \n");
					player.mass = 25.0f;
				}
				if (glfwGetKey(window.getWindow(), GLFW_KEY_M)) {
					printf("Normie Mass \n");
					player.mass = 50.0f;
				}
				if (glfwGetKey(window.getWindow(), GLFW_KEY_B)) {
					printf("THICC Mass \n");
					player.mass = 100.0f;
				}

				if (glfwGetKey(window.getWindow(), GLFW_KEY_T)) {
					printf("Spoopy Blink \n");
					player.dashType = 1;
				}
				if (glfwGetKey(window.getWindow(), GLFW_KEY_Y)) {
					printf("Non-Spoopy Dash \n");
					player.dashType = 0;
				}

				


			}
			else if (game_state == game) {

				healthBar.render(glm::vec3(0.0f, 0.125f, 0.0f), glm::vec3(0.15f * (player.getHealth() / 100.0f), 0.025f, 1.0f), 0.0f, size, shader);

				if (player.getHealth() > 0.0f && player.getPosition().y < 1000.0f) {

					// Acceleration FORWARD AND BACK
					if (GO_FORWARD == 1)	   PLAYER_ACCELERATION = 1;
					else if (GO_BACKWARD == 1) PLAYER_ACCELERATION = -1;
					else					   PLAYER_ACCELERATION = 0;
					player.goFASTER(PLAYER_ACCELERATION, deltaTime);

					// SIDEWAYS MOVEMENT (NON BASHING)
					if (GO_LEFT == 1)		   PLAYER_LEFT_RIGHT = -1;
					else if (GO_RIGHT == 1)	   PLAYER_LEFT_RIGHT = 1;
					else					   PLAYER_LEFT_RIGHT = 0;
					player.sideMovement(PLAYER_LEFT_RIGHT, deltaTime);


					// BASHING MOVEMENT
					if (BASH_RIGHT == 1) BASH_LEFT_RIGHT = 1;
					else if (BASH_LEFT == 1) BASH_LEFT_RIGHT = -1;
					else BASH_LEFT_RIGHT = 0;
					player.sideBash(BASH_LEFT_RIGHT, glfwGetTime(), deltaTime);

					// Shoot
					if (PRESSING_SHOOT_GUN)
					{
						std::cout << "PRESSING GUN" << std::endl;
					}
					else
					{
						std::cout << "NOT" << std::endl;
					}

					gameManager.playerShoot(PRESSING_SHOOT_GUN, PRESSING_SHOOT_ROCKET);

					enemyaitest.update(deltaTime);
					aggresiveEnemy.update(deltaTime);
					gameManager.update(deltaTime);
					gameManager.checkCollisionsPowerups(&player, &powerup);
					for (int i = 0; i < physicsObjects.size(); i++) {
						for (int z = i + 1; z < physicsObjects.size(); z++) {
							gameManager.checkCollisions(physicsObjects[i], physicsObjects[z]);
						}
					}

					//gameManager.checkCollisions(physicsObjects[0], physicsObjects[1]);
					//gameManager.checkCollisions(pPlayer, pAster);
					enemy1.update(deltaTime);
					enemy2.update(deltaTime);
					bhole.update(deltaTime);

					bhole.succ(&player);
					/*aster1.update(deltaTime);
					enemyaitest.update(deltaTime);
					aster1.update(deltaTime);
					aster2.update(deltaTime);
					aster3.update(deltaTime);
					aster4.update(deltaTime);
					aster5.update(deltaTime);
					aster6.update(deltaTime);*/
					for (int i = 0; i < asteroids.size(); i++)
					{
						asteroids.at(i)->update(deltaTime);
					}

					map.update(deltaTime, player.getPosition());
				}
				else if (player.getHealth() > 0.0f && player.getPosition().y > 1000.0) {
					youWinScreen.render(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 0.0f, size, shader);
				}
				else {
					gameOverScreen.render(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), 0.0f, size, shader);
				}

				//printf("%f", enemy.getAcceleration().x);
				printf("%f", enemy1.getVelocity().y);
				printf("\n");
				printf("%f", player.getVelocity().y);
				printf("\n");




				// Render entities
				for (int i = 0; i < asteroids.size(); i++)
				{
					asteroids.at(i)->render(shader);
				}

				
				shader.enable();
				AttributeBinding(shader.getShaderID());
				
				enemy1.render(shader);
				enemy2.render(shader);
				bhole.render(shader);
				powerup.render(shader);
				gameManager.renderAll(shader);

				particleShader.enable();
				AttributeBinding(particleShader.getShaderID());
				drawParticles(particleShader.getShaderID(), glm::vec3(0, 0.01, 0), particleSize);
				particleShader.disable();

				shader.enable();
				AttributeBinding(shader.getShaderID());
				map.renderRoad(shader);
				map.render(shader);
			
			}
			
		//	glDrawArrays(GL_TRIANGLES, 0, 6); // if glDrawArrays be used, glDrawElements will be ignored 

            // Update other events like input handling
            glfwPollEvents();

            // Push buffer drawn in the background onto the display
            glfwSwapBuffers(window.getWindow());
        }
    }
    catch (std::exception &e){
		// print exception and sleep so error can be read
        PrintException(e);
		std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    }

    return 0;
}


 