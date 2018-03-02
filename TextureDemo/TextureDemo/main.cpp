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
#include "Bullet.h"
#include "HUD.h"
#include "GameManager.h"

// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Multiple Sprites Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(0.0, 0.0, 0.2);

// Global texture info
GLuint tex[6];

// Input bools
bool PRESSING_FORWARD;
bool PRESSING_BACK;
bool PRESSING_BASH_R;
bool PRESSING_BASH_L;
bool BASHING;
bool BASHING_STARTED;

/*bool PRESSING_SHOOT_GUN_DOWN;
bool PRESSING_SHOOT_GUN_HOLD;*/

bool PRESSING_SHOOT_GUN;
bool PRESSING_SHOOT_ROCKET;
bool PRESSING_SWITCH_WEAPONS;

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
	glGenTextures(6, tex);
	setthisTexture(tex[0], "blueships1.png");
	setthisTexture(tex[1], "orb.png");
	setthisTexture(tex[2], "saw.png");
	setthisTexture(tex[3], "crosshairs.png");
	setthisTexture(tex[4], "bullet.png");
	setthisTexture(tex[5], "rocket.png");

	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glBindTexture(GL_TEXTURE_2D, tex[5]);
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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create geometry of the square
		int size = CreateSquare();

        // Set up shaders
		Shader shader("shader.vert", "shader.frag"); 

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

		Player player(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[0], size);
		Enemy enemy(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f), 0.0f, tex[1], size, &player);

		Enemy enemies[] = { enemy };
		
		gameManager.setPlayer(&player);
		gameManager.setEnemies(enemies);

		//TESTING FOR PUSHING
		int GO_FORWARD = glfwGetKey(window.getWindow(), GLFW_KEY_W);
		int GO_BACKWARD = glfwGetKey(window.getWindow(), GLFW_KEY_S);
		int GO_LEFT = glfwGetKey(window.getWindow(), GLFW_KEY_A);
		int GO_RIGHT = glfwGetKey(window.getWindow(), GLFW_KEY_D);
		int BASH_RIGHT = glfwGetKey(window.getWindow(), GLFW_KEY_E);
		int BASH_LEFT = glfwGetKey(window.getWindow(), GLFW_KEY_Q);

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
			GO_FORWARD = glfwGetKey(window.getWindow(), GLFW_KEY_W);
			GO_BACKWARD = glfwGetKey(window.getWindow(), GLFW_KEY_S);
			GO_LEFT = glfwGetKey(window.getWindow(), GLFW_KEY_A);
			GO_RIGHT = glfwGetKey(window.getWindow(), GLFW_KEY_D);
			BASH_RIGHT = glfwGetKey(window.getWindow(), GLFW_KEY_E);
			BASH_LEFT = glfwGetKey(window.getWindow(), GLFW_KEY_Q);

			// Acceleration FORWARD AND BACK
			if	(GO_FORWARD == 1)	   PLAYER_ACCELERATION =  1;
			else if (GO_BACKWARD == 1) PLAYER_ACCELERATION = -1;
			else					   PLAYER_ACCELERATION =  0;
			player.goFASTER(PLAYER_ACCELERATION, deltaTime);

			// SIDEWAYS MOVEMENT (NON BASHING)
			if (GO_LEFT == 1)		   PLAYER_LEFT_RIGHT = -1;
			else if (GO_RIGHT == 1)	   PLAYER_LEFT_RIGHT = 1;
			else					   PLAYER_LEFT_RIGHT = 0;
			player.sideMovement(PLAYER_LEFT_RIGHT, deltaTime);


			// BASHING MOVEMENT
			if (BASH_RIGHT == 1 || BASH_LEFT == 1 && BASHING == false) { 
				BASHING_STARTED = true;
				BASHING = true; 
			}

			if (BASHING_STARTED == true) {
				//save ship position +- 5metres
				BASHING_STARTED = false;
			}



			printf("%d", PLAYER_LEFT_RIGHT);
			printf("\n");

			// Get mouse input for turret
			double mouseX, mouseY;
			glfwGetCursorPos(window.getWindow(), &mouseX, &mouseY);
			float screenSpaceMouseX = (mouseX / window_width_g) * 2 - 1;
			float screenSpaceMouseY = -((mouseY / window_height_g) * 2 - 1);
			gameManager.setMousePos(screenSpaceMouseX, screenSpaceMouseY);

			// Shoot
			gameManager.playerShoot(PRESSING_SHOOT_GUN, PRESSING_SHOOT_ROCKET);

			// Update entities
			/*player.update(deltaTime);
			enemy.update(deltaTime);*/
			gameManager.update(deltaTime);

			// Render entities
			//player.render(shader);
			//enemy.render(shader);
			gameManager.renderAll(shader);

			/*for (auto &bullet : player.getBullets()) {
				bullet.render(shader);
			}

			for (auto &rocket : player.getRockets()) {
				rocket.render(shader);
			}*/
			
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


 