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

	//initialize debugDrawer for simulation
	bajs = new Renderer(helloWorld);

	glutMainLoop();

	return 0;
}

void render()
{
	//transforms
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.1,0.1,0.1);
	glRotatef(30.0, 1.0, 0.5, 0.0);

	//draw scene
	bajs->render();

	//must have
	glutSwapBuffers();
	glutPostRedisplay();
}

void update()
{
	helloWorld->step();
}