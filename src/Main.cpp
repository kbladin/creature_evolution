
// 🐢
#include "SettingsManager.h"
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Simulation.h"
#include "Renderer.h"

#include "WindowsManager.h"
#include "EvolutionManager.h"
#include <Shader.hpp>
#include <SceneManager.h>
#include <WormBulletCreature.h>


Simulation* helloWorld;
Renderer* render_engine;
SceneManager* scene;
int width, height;

int main(){

	WindowsManager wm; // = new WindowsManager();
	wm.setVariables(); // get info from window, write to settingsmanager

	EvolutionManager em;// = new EvolutionManager();
	std::cout << "Started the simulation process..." << std::endl;
	em.startEvolutionProcess(); // start the whole evolution process! 
	em.printBestFitnessValues();

	int generation; 
	std::cout << "Which generation would you like to show? ";
	std::cin >> generation; 

	Creature best = em.getBestCreatureFromGeneration(generation);

	//The rendering stuff
	GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    // We want the newest version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    
	/* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	//The while true loop is so that the rendering can be re-done if
	//it does not draw
	//while (true) {
	//initalize simulation
	//helloWorld = new Simulation(best.GetChromosome().GetGene());
	WormBulletCreature *worm = new WormBulletCreature(best.GetChromosome().GetGene(), btVector3(0,0,0));
	helloWorld = new Simulation(); 
	helloWorld->AddCreatureToWorld(worm);
   
	scene = new SceneManager();
	scene->CreateNodesFromBulletCreature(worm);

    
    // Print current OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	render_engine = new Renderer(scene);
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
    while (!glfwWindowShouldClose(window))
    {
		helloWorld->Step(1/60.0f);
        
        scene->UpdateNodes();
        //scene->PrintPhysicsNodes();
		render_engine->render();
        glfwSwapBuffers(window);

        glfwPollEvents();
	}

	helloWorld->RemoveCreatureFromWorld(worm);
	delete worm; 

	delete helloWorld;
	delete render_engine;
	delete scene;
	glfwTerminate();

	return 0;
}
