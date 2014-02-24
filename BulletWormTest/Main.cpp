#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Simulation.h"
#include "Renderer.h"


#define kWindowWidth 800
#define kWindowHeight 800

void render();
void update();

int current_time;

Simulation* helloWorld;
Renderer* bajs;

int main (int argc, char** argv) {
	current_time = glutGet(GLUT_ELAPSED_TIME);
	//for(int i=0; i<1; i++) simulation->advance();
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutInit(&argc, argv);
	glutInitDisplayString("samples stencil>=3 rgb double depth");
	glutCreateWindow("Bullet Test");
	glutDisplayFunc(render);
	glutIdleFunc(update);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	//initalize simulation
	helloWorld = new Simulation();

	//initialize debugDrawer
	bajs = new Renderer(helloWorld->getDynamicsWorld());

	glutMainLoop();

	return 0;
}

void render()
{
	bajs->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void update()
{
	helloWorld->step();
}