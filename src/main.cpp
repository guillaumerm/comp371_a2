//example skeleton code 2019 winter comp371
//modified from http://learnopengl.com/

#include <GL/glew.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Object.h"
#include "OBJloader.h"  //include the object loadr
#include "shaderloader.h"
using namespace std;

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 800;
GLFWwindow *window;

Camera camera = Camera();
Object object = Object();

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	//Keeps the previsou ypos of the cursor
	static double prev_ypos = -1;

	//Initialize the prev_ypos if first cursor_position_callback
	if(prev_ypos == -1)
		prev_ypos = ypos;

	//Move into/out of the scene (assumed that means chaning fov) only when GLFW_MOUSE_BUTTON_LEFT is press
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
	}
	
	// Keeping track of ypos
	prev_ypos = ypos;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwSetCursorPosCallback(window, cursor_position_callback);
	} else {
		glfwSetCursorPosCallback(window, NULL);
	}
}

// Is called whenever a key is pressed/released via GLFW
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// If the key is being release ignore it
	if(action == GLFW_RELEASE){
		return;
	}

	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_R) {
		camera.reset();
		object.reset();
	}
	else if (key == GLFW_KEY_W) {
		camera.moveForward();
	}
	else if (key == GLFW_KEY_S) {
		camera.moveBackward();
	}
	else if (key == GLFW_KEY_A) {
		camera.moveRight();
	}
	else if (key == GLFW_KEY_D) {
		camera.moveLeft();
	}
	else if (key == GLFW_KEY_UP) {
		camera.pitch(-5.0f);
	}
	else if (key == GLFW_KEY_DOWN) {
		camera.pitch(5.0f);
	}
	else if (key == GLFW_KEY_RIGHT) {
		camera.yaw(5.0f);
	}
	else if (key == GLFW_KEY_LEFT) {
		camera.yaw(-5.0f);
	}
	else if (key == GLFW_KEY_J) {
		object.translate(glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if (key == GLFW_KEY_L) {
		object.translate(glm::vec3(-1.0f, 0.0f, 0.0f));
	}
	else if (key == GLFW_KEY_I) {
		object.translate(glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if (key == GLFW_KEY_K) {
		object.translate(glm::vec3(0.0f, -1.0f, 0.0f));
	}
	else if (key == GLFW_KEY_PAGE_UP) {
		object.translate(glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else if (key == GLFW_KEY_PAGE_DOWN) {
		object.translate(glm::vec3(0.0f, 0.0f, -1.0f));
	}
	else if (key == GLFW_KEY_O) {
		object.setScale(glm::vec3(1.1f, 1.1f, 1.1f));
	}
	else if (key == GLFW_KEY_P) {
		object.setScale(glm::vec3(0.9f, 0.9f, 0.9f));
	}
	else if (key == GLFW_KEY_B) {
		if(object.getPitch() + 1.0f > 360.0f){
			object.setPitch(0.0f);
		} else {
			object.setPitch(object.getPitch() + 1.0f);
		}
	}
	else if (key == GLFW_KEY_N) {
		if(object.getYaw() + 1.0f > 360.0f){
			object.setYaw(0.0f);
		} else {
			object.setYaw(object.getYaw() + 1.0f);
		}
	}
	else if (key == GLFW_KEY_E) {
		if(object.getRoll() + 1.0f > 360.0f){
			object.setRoll(0.0f);
		} else {
			object.setRoll(object.getRoll() + 1.0f);
		}
	}
}

// Taken from https://learnopengl.com/ (https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/6.3.coordinate_systems_multiple/coordinate_systems_multiple.cpp) Not really used in this assignment.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int init() {
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//WINDOW
	window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 2", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//Define the depth buffer and enable it
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}
	return 0;
}
// The MAIN function, from here we start the application and run the game loop
int main()
{
	if (init() != 0)
		return EXIT_FAILURE;
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Build and compile our shader program
	// Vertex shader

	GLuint shader = loadSHADER("./shaders/vertex.shader", "./shaders/fragment.shader");
	glUseProgram(shader);
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
	loadOBJ("./objects/cube.obj", indices, vertices, normals, UVs); //read the vertices from the cat.obj file

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint verticesVBO;
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	GLuint normalsVBO;
	glGenBuffers(1, &normalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);


	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW);

	glBindVertexArray(0);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer and depth buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		//Building a perspective view
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		// Constructing the ctm (camera transformation matrix)
		
		model = glm::scale(model, object.getScale());
		// Construct the model_rotation matrix
		glm::mat4 model_rotation = glm::rotate(glm::mat4(1.0f), glm::radians(object.getRoll()), glm::vec3(0,0,1))*glm::rotate(glm::mat4(1.0f), glm::radians(object.getYaw()), glm::vec3(0, 1, 0))* glm::rotate(glm::mat4(1.0f), glm::radians(object.getPitch()), glm::vec3(1,0,0));
		model *= model_rotation;
		model = glm::translate(model, object.getPosition());

		view = glm::lookAt(camera.getPosition(), camera.getFront() + camera.getPosition(), camera.getUp());

		projection = glm::perspective(glm::radians(camera.getFov()), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		//Passing the ctm (camera transformation matrix) to the shaders
		int modelLocation = glGetUniformLocation(shader, "model");
		int viewLocation = glGetUniformLocation(shader, "view");
		int projectionLocation = glGetUniformLocation(shader, "projection");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1, glm::value_ptr(glm::vec3(1,1,1)));
		glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, glm::value_ptr(glm::vec3(1,0,0)));
		glUniform3fv(glGetUniformLocation(shader, "lightPosition"), 1, glm::value_ptr(glm::vec3(0,5,0)));
		glUniform3fv(glGetUniformLocation(shader, "viewPosition"), 1, glm::value_ptr(camera.getPosition()));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
