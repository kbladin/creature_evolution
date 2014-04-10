#ifndef EVOLUTIONMANAGER_H
#define EVOLUTIONMANAGER_H
#include <iostream>

#include <vector>
#include <ctime>

#include "Creature.h"
#include "Simulation.h"
#include "AutoInitRNG.h"


typedef std::vector<Creature> Population;

//! Holds an evolution and can start an evolution process.
//Stores the best creatures from all generations and stores all the generations
class EvolutionManager {

public:
	EvolutionManager();
	~EvolutionManager(void); 

	void startEvolutionProcess();
	Creature GetBestCreatureFromLastGeneration();
	void PrintBestFitnessValues();
	Creature GetBestCreature();

private:
	std::vector<Creature> best_creatures_; // holds alla the best creatures from the populations
	Population current_population_;
    static AutoInitRNG rng_;
	
	Population CreateRandomPopulation(int pop_size);
	void SimulatePopulation();
	void CalculateFitnessOnPopulation();
	void SortPopulation();

	void NextGeneration();

};


#endif // EVOLUTIONMANAGER_H
