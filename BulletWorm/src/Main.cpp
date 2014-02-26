#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
//#define GLFW_INCLUDE_GLCOREARB
#include <GL/glfw3.h>
//#include <GL/freeglut.h>

#include "Simulation.h"
#include "Renderer.h"


#define kWindowWidth 800
#define kWindowHeight 800

void render();
void update();

int current_time;

Simulation* helloWorld;
Renderer* bajs;

GLFWwindow* window;
int width, height;


int main (int argc, char** argv) {

    //glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // We want the newest version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    //glfwSetKeyCallback(window, key_callback);





	/*
	current_time = glutGet(GLUT_ELAPSED_TIME);
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutInit(&argc, argv);
	glutInitDisplayString("samples stencil>=3 rgb double depth");
	glutCreateWindow("Bullet Test");
	glutDisplayFunc(render);
	glutIdleFunc(update);
	*/
	// start GLEW extension handler
	//glewExperimental = GL_TRUE;
	//glewInit();

	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);

	//initalize simulation
	helloWorld = new Simulation();

	//initialize debugDrawer for simulation
	bajs = new Renderer(helloWorld);




    while (!glfwWindowShouldClose(window)){
        glfwGetFramebufferSize(window, &width, &height);
        // DRAW
        update();

        render();

        //Swap draw buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


	//glutMainLoop();

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
	/*
	glutSwapBuffers();
	glutPostRedisplay();
	*/
}

void update()
{
	helloWorld->step();
}