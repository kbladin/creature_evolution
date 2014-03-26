#ifndef EVOLUTION_H
#define EVOLUTION_H

// C++
#include <vector>
#include <cassert>
#include "SettingsManager.h"
#include "Population.h"
//typedef std::vector<Creature> Population;

//! Evolves a population based on elitism, mutation and crossover ratio.

class Evolution {
private:
	const static int TOURNAMENT_SIZE_ = 3;

	std::vector<Creature> TournamentSelection(const Population &population);
	Creature Roulette(float total_fitness, const Population &population);
	float CalculateTotalFitness(const Population &population);

	static AutoInitRNG rng_;

public:
	~Evolution(void); 

	Population nextGeneration(const Population &population); // uppdatera den nuvarande populationen sen kanske ist?
};


#endif // EVOLUTION_H