#ifndef EVOLUTIONMANAGER_H
#define EVOLUTIONMANAGER_H
#include <iostream>

#include "Evolution.h"
#include "Creature.h"
#include "Population.h"
#include <vector>
#include <ctime>

//! Holds an evolution and can start an evolution process. Stores the best creatures from all generations and stores all the generationss

class EvolutionManager {
private:
	Evolution *ev_; // holds the variables for the evolution. 
	int max_generations_;

	std::vector<Creature> bestCreatures_; // holds alla the best creatures from the populations
	std::vector<Population> allPopulations_; // if we want to store alla the populations! 

public:
	EvolutionManager();
	~EvolutionManager(void); 

	void startEvolutionProcess();

	Creature getBestCreatureFromLastGeneration();
	Creature getBestCreatureFromGeneration(int generation);
	void printBestFitnessValues();
};


#endif // EVOLUTIONMANAGER_H