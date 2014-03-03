#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Simulation.h"
#include "Renderer.h"

void render();
void update();

int current_time;

Simulation* helloWorld;
Renderer* render_engine;

GLFWwindow* window;
int width, height;


int main (int argc, char** argv) {

	//initalize simulation
	helloWorld = new Simulation();

	//initialize debugDrawer for simulation
	render_engine = new Renderer(helloWorld, true);
	
	GLFWwindow* window;

	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	
	while (!glfwWindowShouldClose(window)) {
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float) height;
		update();
		render();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	return 0;
}

void render()
{
	//transforms
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.1,0.1,0.1);
	glRotatef(30.0, 0.5, 1.0, 0.0);

	//draw scene
	render_engine->render();
}

void update()
{
	helloWorld->step();
}