
// 🐢
#include "WindowsManager.h"
#include "SettingsManager.h"
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Simulation.h"
#include "Renderer.h"

#include "EvolutionManager.h"
#include <Shader.hpp>
#include <SceneManager.h>
#include <WormBulletCreature.h>


Simulation* helloWorld;
Renderer* render_engine;
SceneManager* scene;
int width, height;

int main(){

	WindowsManager wm(640,480); // = new WindowsManager();
	wm.setVariables(); // get info from window, write to settingsmanager

	EvolutionManager em;// = new EvolutionManager();
	std::cout << "Started the simulation process..." << std::endl;
	em.startEvolutionProcess(); // start the whole evolution process! 
	em.printBestFitnessValues();

	int generation; 
	std::cout << "Which generation would you like to show? ";
	std::cin >> generation; 

	Creature best = em.getBestCreatureFromGeneration(generation);

	WormBulletCreature *worm = new WormBulletCreature(best.GetChromosome().GetGene(), btVector3(0,0,0));
	helloWorld = new Simulation(); 
	helloWorld->AddCreatureToWorld(worm);
   
	scene = new SceneManager();
	scene->CreateNodesFromBulletCreature(worm);
  	render_engine = new Renderer(scene);
    
  	wm.DisplayAndRender(helloWorld, scene, render_engine);

	helloWorld->RemoveCreatureFromWorld(worm);
	delete worm; 

	delete helloWorld;
	delete render_engine;
	delete scene;

	return 0;
}
