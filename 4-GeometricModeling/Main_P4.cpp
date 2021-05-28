#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 0.650, 0.650, 0.650, /*Grey*/
		0.5f, -0.5f, 0.5f,  0.650, 0.650, 0.650,
		0.5f,  0.5f, 0.5f,  0.650, 0.650, 0.650,
		0.5f,  0.5f, 0.5f,  0.650, 0.650, 0.650,
		-0.5f,  0.5f, 0.5f, 0.650, 0.650, 0.650,
		-0.5f, -0.5f, 0.5f, 0.650, 0.650, 0.650,

		-0.5f, -0.5f,-0.5f, 0.650, 0.650, 0.650,
		 0.5f, -0.5f,-0.5f, 0.650, 0.650, 0.650,
		 0.5f,  0.5f,-0.5f, 0.650, 0.650, 0.650,
		 0.5f,  0.5f,-0.5f, 0.650, 0.650, 0.650,
		-0.5f,  0.5f,-0.5f, 0.650, 0.650, 0.650,
		-0.5f, -0.5f,-0.5f, 0.650, 0.650, 0.650,

		 0.5f, -0.5f,  0.5f,  0.650, 0.650, 0.650,
		 0.5f, -0.5f, -0.5f,  0.650, 0.650, 0.650,
		 0.5f,  0.5f, -0.5f,  0.650, 0.650, 0.650,
		 0.5f,  0.5f, -0.5f,  0.650, 0.650, 0.650,
		 0.5f,  0.5f,  0.5f,  0.650, 0.650, 0.650,
		 0.5f,  -0.5f, 0.5f,  0.650, 0.650, 0.650,

		-0.5f,  0.5f,  0.5f,  0.650, 0.650, 0.650,
		-0.5f,  0.5f, -0.5f,  0.650, 0.650, 0.650,
		-0.5f, -0.5f, -0.5f,  0.650, 0.650, 0.650,
		-0.5f, -0.5f, -0.5f,  0.650, 0.650, 0.650,
		-0.5f, -0.5f,  0.5f,  0.650, 0.650, 0.650,
		-0.5f,  0.5f,  0.5f,  0.650, 0.650, 0.650,

		-0.5f, -0.5f, -0.5f, 0.650, 0.650, 0.650,
		0.5f, -0.5f, -0.5f,  0.650, 0.650, 0.650,
		0.5f, -0.5f,  0.5f,  0.650, 0.650, 0.650,
		0.5f, -0.5f,  0.5f,  0.650, 0.650, 0.650,
		-0.5f, -0.5f,  0.5f, 0.650, 0.650, 0.650,
		-0.5f, -0.5f, -0.5f, 0.650, 0.650, 0.650,

		-0.5f,  0.5f, -0.5f, 0.650, 0.650, 0.650,
		0.5f,  0.5f, -0.5f,  0.650, 0.650, 0.650,
		0.5f,  0.5f,  0.5f,  0.650, 0.650, 0.650,
		0.5f,  0.5f,  0.5f,  0.650, 0.650, 0.650,
		-0.5f,  0.5f,  0.5f, 0.650, 0.650, 0.650,
		-0.5f,  0.5f, -0.5f, 0.650, 0.650, 0.650,

		-0.5f, -0.5f, 0.5f, 0.780, 0.780, 0.780, /*Light Gray*/
		0.5f, -0.5f, 0.5f,  0.780, 0.780, 0.780,
		0.5f,  0.5f, 0.5f,  0.780, 0.780, 0.780,
		0.5f,  0.5f, 0.5f,  0.780, 0.780, 0.780,
		-0.5f,  0.5f, 0.5f, 0.780, 0.780, 0.780,
		-0.5f, -0.5f, 0.5f, 0.780, 0.780, 0.780,

		-0.5f, -0.5f,-0.5f, 0.780, 0.780, 0.780,
		 0.5f, -0.5f,-0.5f, 0.780, 0.780, 0.780,
		 0.5f,  0.5f,-0.5f, 0.780, 0.780, 0.780,
		 0.5f,  0.5f,-0.5f, 0.780, 0.780, 0.780,
		-0.5f,  0.5f,-0.5f, 0.780, 0.780, 0.780,
		-0.5f, -0.5f,-0.5f, 0.780, 0.780, 0.780,

		 0.5f, -0.5f,  0.5f,  0.780, 0.780, 0.780,
		 0.5f, -0.5f, -0.5f,  0.780, 0.780, 0.780,
		 0.5f,  0.5f, -0.5f,  0.780, 0.780, 0.780,
		 0.5f,  0.5f, -0.5f,  0.780, 0.780, 0.780,
		 0.5f,  0.5f,  0.5f,  0.780, 0.780, 0.780,
		 0.5f,  -0.5f, 0.5f,  0.780, 0.780, 0.780,

		-0.5f,  0.5f,  0.5f,  0.780, 0.780, 0.780,
		-0.5f,  0.5f, -0.5f,  0.780, 0.780, 0.780,
		-0.5f, -0.5f, -0.5f,  0.780, 0.780, 0.780,
		-0.5f, -0.5f, -0.5f,  0.780, 0.780, 0.780,
		-0.5f, -0.5f,  0.5f,  0.780, 0.780, 0.780,
		-0.5f,  0.5f,  0.5f,  0.780, 0.780, 0.780,

		-0.5f, -0.5f, -0.5f, 0.780, 0.780, 0.780,
		0.5f, -0.5f, -0.5f,  0.780, 0.780, 0.780,
		0.5f, -0.5f,  0.5f,  0.780, 0.780, 0.780,
		0.5f, -0.5f,  0.5f,  0.780, 0.780, 0.780,
		-0.5f, -0.5f,  0.5f, 0.780, 0.780, 0.780,
		-0.5f, -0.5f, -0.5f, 0.780, 0.780, 0.780,

		-0.5f,  0.5f, -0.5f, 0.780, 0.780, 0.780,
		0.5f,  0.5f, -0.5f,  0.780, 0.780, 0.780,
		0.5f,  0.5f,  0.5f,  0.780, 0.780, 0.780,
		0.5f,  0.5f,  0.5f,  0.780, 0.780, 0.780,
		-0.5f,  0.5f,  0.5f, 0.780, 0.780, 0.780,
		-0.5f,  0.5f, -0.5f, 0.780, 0.780, 0.780,


		-0.5f, -0.5f, 0.5f, 0.250, 0.250, 0.250, /*Dark Gray*/
		0.5f, -0.5f, 0.5f,  0.250, 0.250, 0.250,
		0.5f,  0.5f, 0.5f,  0.250, 0.250, 0.250,
		0.5f,  0.5f, 0.5f,  0.250, 0.250, 0.250,
		-0.5f,  0.5f, 0.5f, 0.250, 0.250, 0.250,
		-0.5f, -0.5f, 0.5f, 0.250, 0.250, 0.250,

		-0.5f, -0.5f,-0.5f, 0.250, 0.250, 0.250,
		 0.5f, -0.5f,-0.5f, 0.250, 0.250, 0.250,
		 0.5f,  0.5f,-0.5f, 0.250, 0.250, 0.250,
		 0.5f,  0.5f,-0.5f, 0.250, 0.250, 0.250,
		-0.5f,  0.5f,-0.5f, 0.250, 0.250, 0.250,
		-0.5f, -0.5f,-0.5f, 0.250, 0.250, 0.250,

		 0.5f, -0.5f,  0.5f,  0.250, 0.250, 0.250,
		 0.5f, -0.5f, -0.5f,  0.250, 0.250, 0.250,
		 0.5f,  0.5f, -0.5f,  0.250, 0.250, 0.250,
		 0.5f,  0.5f, -0.5f,  0.250, 0.250, 0.250,
		 0.5f,  0.5f,  0.5f,  0.250, 0.250, 0.250,
		 0.5f,  -0.5f, 0.5f,  0.250, 0.250, 0.250,

		-0.5f,  0.5f,  0.5f,  0.250, 0.250, 0.250,
		-0.5f,  0.5f, -0.5f,  0.250, 0.250, 0.250,
		-0.5f, -0.5f, -0.5f,  0.250, 0.250, 0.250,
		-0.5f, -0.5f, -0.5f,  0.250, 0.250, 0.250,
		-0.5f, -0.5f,  0.5f,  0.250, 0.250, 0.250,
		-0.5f,  0.5f,  0.5f,  0.250, 0.250, 0.250,

		-0.5f, -0.5f, -0.5f, 0.250, 0.250, 0.250,
		0.5f, -0.5f, -0.5f,  0.250, 0.250, 0.250,
		0.5f, -0.5f,  0.5f,  0.250, 0.250, 0.250,
		0.5f, -0.5f,  0.5f,  0.250, 0.250, 0.250,
		-0.5f, -0.5f,  0.5f, 0.250, 0.250, 0.250,
		-0.5f, -0.5f, -0.5f, 0.250, 0.250, 0.250,

		-0.5f,  0.5f, -0.5f, 0.250, 0.250, 0.250,
		0.5f,  0.5f, -0.5f,  0.250, 0.250, 0.250,
		0.5f,  0.5f,  0.5f,  0.250, 0.250, 0.250,
		0.5f,  0.5f,  0.5f,  0.250, 0.250, 0.250,
		-0.5f,  0.5f,  0.5f, 0.250, 0.250, 0.250,
		-0.5f,  0.5f, -0.5f, 0.250, 0.250, 0.250,


		-0.5f, -0.5f, 0.5f, 1.0, 1.0, 1.0, /*White*/
		0.5f, -0.5f, 0.5f,  1.0, 1.0, 1.0,
		0.5f, 0.5f, 0.5f,   1.0, 1.0, 1.0,
		0.5f, 0.5f, 0.5f,   1.0, 1.0, 1.0,
		-0.5f, 0.5f, 0.5f,  1.0, 1.0, 1.0,
		-0.5f, -0.5f, 0.5f, 1.0, 1.0, 1.0,

		-0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
		0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0,
		0.5f, 0.5f, -0.5f,   1.0, 1.0, 1.0,
		0.5f, 0.5f, -0.5f,   1.0, 1.0, 1.0,
		-0.5f, 0.5f, -0.5f,  1.0, 1.0, 1.0,
		-0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,

		0.5f, -0.5f, 0.5f,  1.0, 1.0, 1.0,
		0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
		0.5f, 0.5f, -0.5f,  1.0, 1.0, 1.0,
		0.5f, 0.5f, -0.5f,  1.0, 1.0, 1.0,
		0.5f, 0.5f, 0.5f,   1.0, 1.0, 1.0,
		0.5f, -0.5f, 0.5f,  1.0, 1.0, 1.0,

		-0.5f, 0.5f, 0.5f,   1.0, 1.0, 1.0,
		-0.5f, 0.5f, -0.5f,  1.0, 1.0, 1.0,
		-0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
		-0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
		-0.5f, -0.5f, 0.5f,  1.0, 1.0, 1.0,
		-0.5f, 0.5f, 0.5f,   1.0, 1.0, 1.0,

		-0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,
		0.5f, -0.5f, -0.5f,  1.0, 1.0, 1.0,
		0.5f, -0.5f, 0.5f,   1.0, 1.0, 1.0,
		0.5f, -0.5f, 0.5f,   1.0, 1.0, 1.0,
		-0.5f, -0.5f, 0.5f,  1.0, 1.0, 1.0,
		-0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0,

		-0.5f, 0.5f, -0.5f, 1.0, 1.0, 1.0,
		0.5f, 0.5f, -0.5f,  1.0, 1.0, 1.0,
		0.5f, 0.5f, 0.5f,   1.0, 1.0, 1.0,
		0.5f, 0.5f, 0.5f,   1.0, 1.0, 1.0,
		-0.5f, 0.5f, 0.5f,  1.0, 1.0, 1.0,
		-0.5f, 0.5f, -0.5f, 1.0, 1.0, 1.0,

		-0.5f, -0.5f, 0.5f, 0.160, 0.180, 0.298, /*Navy blue*/
		0.5f, -0.5f, 0.5f,  0.160, 0.180, 0.298,
		0.5f, 0.5f, 0.5f,   0.160, 0.180, 0.298,
		0.5f, 0.5f, 0.5f,   0.160, 0.180, 0.298,
		-0.5f, 0.5f, 0.5f,  0.160, 0.180, 0.298,
		-0.5f, -0.5f, 0.5f, 0.160, 0.180, 0.298,
			
		-0.5f, -0.5f, -0.5f, 0.160, 0.180, 0.298,
		0.5f, -0.5f, -0.5f,  0.160, 0.180, 0.298,
		0.5f, 0.5f, -0.5f,   0.160, 0.180, 0.298,
		0.5f, 0.5f, -0.5f,   0.160, 0.180, 0.298,
		-0.5f, 0.5f, -0.5f,  0.160, 0.180, 0.298,
		-0.5f, -0.5f, -0.5f, 0.160, 0.180, 0.298,

		0.5f, -0.5f, 0.5f, 0.160, 0.180, 0.298,
		0.5f, -0.5f, -0.5f, 0.160, 0.180, 0.298,
		0.5f, 0.5f, -0.5f, 0.160, 0.180, 0.298,
		0.5f, 0.5f, -0.5f, 0.160, 0.180, 0.298,
		0.5f, 0.5f, 0.5f, 0.160, 0.180, 0.298,
		0.5f, -0.5f, 0.5f, 0.160, 0.180, 0.298,

		-0.5f, 0.5f, 0.5f,   0.160, 0.180, 0.298,
		-0.5f, 0.5f, -0.5f,  0.160, 0.180, 0.298,
		-0.5f, -0.5f, -0.5f, 0.160, 0.180, 0.298,
		-0.5f, -0.5f, -0.5f, 0.160, 0.180, 0.298,
		-0.5f, -0.5f, 0.5f,  0.160, 0.180, 0.298,
		-0.5f, 0.5f, 0.5f,   0.160, 0.180, 0.298,

		-0.5f, -0.5f, -0.5f, 0.160, 0.180, 0.298,
		0.5f, -0.5f, -0.5f,  0.160, 0.180, 0.298,
		0.5f, -0.5f, 0.5f,   0.160, 0.180, 0.298,
		0.5f, -0.5f, 0.5f,   0.160, 0.180, 0.298,
		-0.5f, -0.5f, 0.5f,  0.160, 0.180, 0.298,
		-0.5f, -0.5f, -0.5f, 0.160, 0.180, 0.298,

		-0.5f, 0.5f, -0.5f, 0.160, 0.180, 0.298,
		0.5f, 0.5f, -0.5f,  0.160, 0.180, 0.298,
		0.5f, 0.5f, 0.5f,   0.160, 0.180, 0.298,
		0.5f, 0.5f, 0.5f,   0.160, 0.180, 0.298,
		-0.5f, 0.5f, 0.5f,  0.160, 0.180, 0.298,
		-0.5f, 0.5f, -0.5f, 0.160, 0.180, 0.298,

		-0.5f, -0.5f, 0.5f, 0.298, 0.807, 0.980, /*blue*/
		0.5f, -0.5f, 0.5f,  0.298, 0.807, 0.980,
		0.5f, 0.5f, 0.5f,   0.298, 0.807, 0.980,
		0.5f, 0.5f, 0.5f,   0.298, 0.807, 0.980,
		-0.5f, 0.5f, 0.5f,  0.298, 0.807, 0.980,
		-0.5f, -0.5f, 0.5f, 0.298, 0.807, 0.980,

		-0.5f, -0.5f, -0.5f, 0.298, 0.807, 0.980,
		0.5f, -0.5f, -0.5f,  0.298, 0.807, 0.980,
		0.5f, 0.5f, -0.5f,   0.298, 0.807, 0.980,
		0.5f, 0.5f, -0.5f,   0.298, 0.807, 0.980,
		-0.5f, 0.5f, -0.5f,  0.298, 0.807, 0.980,
		-0.5f, -0.5f, -0.5f, 0.298, 0.807, 0.980,

		0.5f, -0.5f, 0.5f,  0.298, 0.807, 0.980,
		0.5f, -0.5f, -0.5f, 0.298, 0.807, 0.980,
		0.5f, 0.5f, -0.5f,  0.298, 0.807, 0.980,
		0.5f, 0.5f, -0.5f,  0.298, 0.807, 0.980, 
		0.5f, 0.5f, 0.5f,   0.298, 0.807, 0.980,
		0.5f, -0.5f, 0.5f,  0.298, 0.807, 0.980,

		-0.5f, 0.5f, 0.5f,   0.298, 0.807, 0.980,
		-0.5f, 0.5f, -0.5f,  0.298, 0.807, 0.980,
		-0.5f, -0.5f, -0.5f, 0.298, 0.807, 0.980,
		-0.5f, -0.5f, -0.5f, 0.298, 0.807, 0.980,
		-0.5f, -0.5f, 0.5f,  0.298, 0.807, 0.980,
		-0.5f, 0.5f, 0.5f,   0.298, 0.807, 0.980,

		-0.5f, -0.5f, -0.5f, 0.298, 0.807, 0.980,
		0.5f, -0.5f, -0.5f,  0.298, 0.807, 0.980,
		0.5f, -0.5f, 0.5f,   0.298, 0.807, 0.980,
		0.5f, -0.5f, 0.5f,   0.298, 0.807, 0.980,
		-0.5f, -0.5f, 0.5f,  0.298, 0.807, 0.980,
		-0.5f, -0.5f, -0.5f, 0.298, 0.807, 0.980,

		-0.5f, 0.5f, -0.5f, 0.298, 0.807, 0.980,
		0.5f, 0.5f, -0.5f,  0.298, 0.807, 0.980,
		0.5f, 0.5f, 0.5f,   0.298, 0.807, 0.980,
		0.5f, 0.5f, 0.5f,   0.298, 0.807, 0.980,
		-0.5f, 0.5f, 0.5f,  0.298, 0.807, 0.980,
		-0.5f, 0.5f, -0.5f, 0.298, 0.807, 0.980,

		-0.5f, -0.5f, 0.5f, 1, 0.980, 0.058,	 /*Yellow*/
		0.5f, -0.5f, 0.5f,  1, 0.980, 0.058,
		0.5f, 0.5f, 0.5f,   1, 0.980, 0.058,
		0.5f, 0.5f, 0.5f,   1, 0.980, 0.058,
		-0.5f, 0.5f, 0.5f,  1, 0.980, 0.058,
		-0.5f, -0.5f, 0.5f, 1, 0.980, 0.058,

		-0.5f, -0.5f, -0.5f, 1, 0.980, 0.058,
		0.5f, -0.5f, -0.5f,  1, 0.980, 0.058,
		0.5f, 0.5f, -0.5f,   1, 0.980, 0.058,
		0.5f, 0.5f, -0.5f,   1, 0.980, 0.058,
		-0.5f, 0.5f, -0.5f,  1, 0.980, 0.058,
		-0.5f, -0.5f, -0.5f, 1, 0.980, 0.058,

		0.5f, -0.5f, 0.5f,  1, 0.980, 0.058,
		0.5f, -0.5f, -0.5f, 1, 0.980, 0.058,
		0.5f, 0.5f, -0.5f,  1, 0.980, 0.058,
		0.5f, 0.5f, -0.5f,  1, 0.980, 0.058,
		0.5f, 0.5f, 0.5f,   1, 0.980, 0.058,
		0.5f, -0.5f, 0.5f,  1, 0.980, 0.058,

		-0.5f, 0.5f, 0.5f,   1, 0.980, 0.058,
		-0.5f, 0.5f, -0.5f,  1, 0.980, 0.058,
		-0.5f, -0.5f, -0.5f, 1, 0.980, 0.058,
		-0.5f, -0.5f, -0.5f, 1, 0.980, 0.058,
		-0.5f, -0.5f, 0.5f,  1, 0.980, 0.058,
		-0.5f, 0.5f, 0.5f,   1, 0.980, 0.058,

		-0.5f, -0.5f, -0.5f, 1, 0.980, 0.058,
		0.5f, -0.5f, -0.5f,  1, 0.980, 0.058,
		0.5f, -0.5f, 0.5f,   1, 0.980, 0.058, 
		0.5f, -0.5f, 0.5f,   1, 0.980, 0.058,
		-0.5f, -0.5f, 0.5f,  1, 0.980, 0.058,
		-0.5f, -0.5f, -0.5f, 1, 0.980, 0.058,

		-0.5f, 0.5f, -0.5f, 1, 0.980, 0.058,
		0.5f, 0.5f, -0.5f,  1, 0.980, 0.058,
		0.5f, 0.5f, 0.5f,   1, 0.980, 0.058,
		0.5f, 0.5f, 0.5f,   1, 0.980, 0.058,
		-0.5f, 0.5f, 0.5f,  1, 0.980, 0.058,
		-0.5f, 0.5f, -0.5f, 1, 0.980, 0.058,


		-0.5f, -0.5f, 0.5f, 0.945, 0.694, 0.858,	 /*Pink*/
		0.5f, -0.5f, 0.5f,  0.945, 0.694, 0.858,
		0.5f, 0.5f, 0.5f,   0.945, 0.694, 0.858,
		0.5f, 0.5f, 0.5f,   0.945, 0.694, 0.858,
		-0.5f, 0.5f, 0.5f,  0.945, 0.694, 0.858,
		-0.5f, -0.5f, 0.5f, 0.945, 0.694, 0.858,

		-0.5f, -0.5f, -0.5f, 0.945, 0.694, 0.858,
		0.5f, -0.5f, -0.5f,  0.945, 0.694, 0.858,
		0.5f, 0.5f, -0.5f,   0.945, 0.694, 0.858,
		0.5f, 0.5f, -0.5f,   0.945, 0.694, 0.858,
		-0.5f, 0.5f, -0.5f,  0.945, 0.694, 0.858,
		-0.5f, -0.5f, -0.5f, 0.945, 0.694, 0.858,

		0.5f, -0.5f, 0.5f,  0.945, 0.694, 0.858,
		0.5f, -0.5f, -0.5f, 0.945, 0.694, 0.858,
		0.5f, 0.5f, -0.5f,  0.945, 0.694, 0.858,
		0.5f, 0.5f, -0.5f,  0.945, 0.694, 0.858,
		0.5f, 0.5f, 0.5f,   0.945, 0.694, 0.858,
		0.5f, -0.5f, 0.5f,  0.945, 0.694, 0.858,

		-0.5f, 0.5f, 0.5f,   0.945, 0.694, 0.858,
		-0.5f, 0.5f, -0.5f,  0.945, 0.694, 0.858,
		-0.5f, -0.5f, -0.5f, 0.945, 0.694, 0.858,
		-0.5f, -0.5f, -0.5f, 0.945, 0.694, 0.858,
		-0.5f, -0.5f, 0.5f,  0.945, 0.694, 0.858,
		-0.5f, 0.5f, 0.5f,   0.945, 0.694, 0.858,

		-0.5f, -0.5f, -0.5f, 0.945, 0.694, 0.858,
		0.5f, -0.5f, -0.5f,  0.945, 0.694, 0.858,
		0.5f, -0.5f, 0.5f,   0.945, 0.694, 0.858,
		0.5f, -0.5f, 0.5f,   0.945, 0.694, 0.858,
		-0.5f, -0.5f, 0.5f,  0.945, 0.694, 0.858,
		-0.5f, -0.5f, -0.5f, 0.945, 0.694, 0.858,

		-0.5f, 0.5f, -0.5f, 0.945, 0.694, 0.858,
		0.5f, 0.5f, -0.5f,  0.945, 0.694, 0.858,
		0.5f, 0.5f, 0.5f,   0.945, 0.694, 0.858,
		0.5f, 0.5f, 0.5f,   0.945, 0.694, 0.858,
		-0.5f, 0.5f, 0.5f,  0.945, 0.694, 0.858,
		-0.5f, 0.5f, -0.5f, 0.945, 0.694, 0.858,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
	

		//glDrawArrays(GL_TRIANGLES, 0, 36); Gris
		//glDrawArrays(GL_TRIANGLES, 36, 36); Gris claro
		//glDrawArrays(GL_TRIANGLES, 72, 36); Gris oscuro
		//glDrawArrays(GL_TRIANGLES, 108, 36); Blanco
		//glDrawArrays(GL_TRIANGLES, 144, 36); Azul marino
		//glDrawArrays(GL_TRIANGLES, 180, 36); Azul
		//glDrawArrays(GL_TRIANGLES, 216, 36); Amarillo
		//glDrawArrays(GL_TRIANGLES, 252, 36); Rosa

		//model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		/*Head*/
		model = glm::mat4(1);
		model = glm::scale(model, glm::vec3(3.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/*Eye brows*/
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.83f, 0.16f, 0.84f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.83f, 0.16f, 0.84f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		/*Eyes*/
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.7166, 0.086f, 0.841f));
		model = glm::scale(model, glm::vec3(0.77f, 0.86f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.7166f, 0.086f, 0.841f));
		model = glm::scale(model, glm::vec3(0.77f, 0.86f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.66f, -0.1666f, 0.842f));
		model = glm::scale(model, glm::vec3(0.33f, 0.33f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.66f, -0.1666f, 0.842f));
		model = glm::scale(model, glm::vec3(0.33f, 0.33f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		/*Nose*/
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, 1.16f));
		model = glm::scale(model, glm::vec3(0.333f, 0.333f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 252, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -0.66666f, 1.15f));
		model = glm::scale(model, glm::vec3(1.0f, 0.66f, 0.33f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		/*Ears*/
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.16f, 2.0f, -0.66f));
		model = glm::scale(model, glm::vec3(0.333f, 2.0f, 0.65f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 252, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.16f, 1.85f, -0.67f));
		model = glm::scale(model, glm::vec3(1.0f, 1.7f, 0.66f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.16f, 3.0f, -0.67f));
		model = glm::scale(model, glm::vec3(1.0f, 0.66f, 0.66f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.16f, 2.0f, -0.66f));
		model = glm::scale(model, glm::vec3(0.333f, 2.0f, 0.65f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 252, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.16f, 1.85f, -0.67f));
		model = glm::scale(model, glm::vec3(1.0f, 1.7f, 0.66f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.16f, 3.0f, -0.67f));
		model = glm::scale(model, glm::vec3(1.0f, 0.66f, 0.66f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		/*Neck*/
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -1.16f, 0.0f));
		model = glm::scale(model, glm::vec3(1.3333f, 0.33333f, 0.6666f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 36);

		/*Vest*/
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.3333f, 1.3333f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);

		/*Badge*/
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.5f, -1.8666f, 0.51f));
		model = glm::scale(model, glm::vec3(0.3333f, 0.33333f, 0.3333f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 216, 36);

		glBindVertexArray(0);


			

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 1.0f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 1.0f;
 }


