#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "AutoInitRNG.h"
#include "Creature.h"
#include <vector>
#include <cassert>

class Evolution {
private:
	const static int TOURNAMENT_SIZE_ = 3; // används i nextGen.

	float elitism_; // dessa kanske vara const istället?
	float mutation_;
	float crossover_;

	std::vector<Creature> SelectParents(const std::vector<Creature> &population);
	float Evolution::CalculateTotalFitness(const std::vector<Creture> &population)
	
	static AutoInitRNG rng_;

public:
	Evolution(float crossover_ratio, float elitism_ratio, 
		float mutation_ratio);  // int size sen kanske? 
	~Evolution(void); 

	std::vector<Creature> nextGeneration(const std::vector<Creature> &population); // uppdaterar den nuvarande populationen?
	std::vector<Creature> nextGenerationMixedMating( const std::vector<Creature> &population );
	Creature Evolution::Roulette(const std::vector<Creature> &population)

};


#endif // EVOLUTION_H