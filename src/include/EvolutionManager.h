#ifndef EVOLUTIONMANAGER_H
#define EVOLUTIONMANAGER_H
#include <iostream>

#include "Evolution.h"
#include "Creature.h"
#include <vector>
#include <ctime>

typedef std::vector<Creature> Population;

class EvolutionManager {
private:
	Evolution *ev_; // holds the variables for the evolution. 
	int max_generations_;
	int population_size_;

	std::vector<Creature> bestCreatures_; // holds alla the best creatures from the populations
	std::vector<Population> allPopulations_; // if we want to store alla the populations! 

public:
	EvolutionManager();
	~EvolutionManager(void); 

	void startEvolutionProcess();

	Creature getBestCreatureFromLastGeneration();
	void printBestFitnessValues();
};


#endif // EVOLUTIONMANAGER_H