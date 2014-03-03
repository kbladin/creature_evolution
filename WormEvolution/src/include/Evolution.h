#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "AutoInitRNG.h"
#include "Creature.h"
#include <vector>
#include <cassert>

typedef std::vector<Creature> Population;  // define the population as a vector of creatures

class Evolution {
private:
	const static int TOURNAMENT_SIZE_ = 3; // används i nextGen.

	float elitism_; // dessa kanske vara const istället?
	float mutation_;
	float crossover_;

	Population TournamentSelection(const Population &population);
	Creature Roulette(float total_fitness, const Population &population);
	float CalculateTotalFitness(const Population &population);

	static AutoInitRNG rng_;

public:
	Evolution(float crossover_ratio, float elitism_ratio, 
		float mutation_ratio);  // int size sen kanske? 
	~Evolution(void); 

	Population nextGeneration(const Population &population); // uppdaterar den nuvarande populationen?
};


#endif // EVOLUTION_H