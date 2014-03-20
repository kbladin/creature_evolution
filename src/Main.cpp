
// 🐢
#include "SettingsManager.h"
#include "Evolution.h"
#include "Creature.h"
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "Simulation.h"
#include "Renderer.h"
#include "WindowsManager.h"
#include "EvolutionManager.h"



int main(){

	WindowsManager wm; // = new WindowsManager();
	wm.setVariables(); // get info from window, write to settingsmanager

	EvolutionManager em;// = new EvolutionManager();
	std::cout << "Started the simulation process..." << std::endl;
	em.startEvolutionProcess(); // start the whole evolution process! 
	em.printBestFitnessValues();

	//Creature best = em.getBestCreatureFromLastGeneration(); // get the best generation
	//
	int generation; 
	std::cout << "Which generation would you like to show? ";
	std::cin >> generation; 

	Creature best = em.getBestCreatureFromGeneration(generation);

 

	return 0;
}
