#include "WindowsManager.h"

//! Constructor
WindowsManager::WindowsManager(){
	std::cout << "Created WindowsManager." << std::endl;
}

//! Destructor
WindowsManager::~WindowsManager(void){
}


void WindowsManager::setVariables(){
	// just for know, read in from user-input from console.
	// no check for wrong input!

	int max_generations, population_size;
	float crossover, elitism, mutation;

	std::cout << "Inside WindowManager, get input and send to SettingsManager" << std::endl;

	std::cout << "Max generations: " ;
	std::cin >> max_generations; 
	std::cout << "Population size: " ;
	std::cin >> population_size; 
	std::cout << "Crossover ratio (0.0-1.0): " ;
	std::cin >> crossover; 
	std::cout << "Elitism ratio (0.0-1.0): " ;
	std::cin >> elitism; 
	std::cout << "Mutation ratio (0.0-1.0): " ;
	std::cin >> mutation;

	SettingsManager::Instance()->setMaxGenerations(max_generations);
	SettingsManager::Instance()->setPopulationSize(population_size);
	SettingsManager::Instance()->setCrossover(crossover);
	SettingsManager::Instance()->setElitism(elitism);
	SettingsManager::Instance()->setMutation(mutation);
}

