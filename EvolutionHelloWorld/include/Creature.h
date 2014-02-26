#ifndef CREATURE_H
#define CREATURE_H

#include "Chromosome.h"
#include "AutoInitRNG.h"
#include <iostream>
#include <string>


class Creature {
private:
	Chromosome chromosome_;

	unsigned int fitness_; 
	static unsigned int CalculateFitness(Chromosome chromsome);
	static AutoInitRNG rng_;

public:
	// Constructor, one that will define the gene_code and one random
	Creature(Chromosome cromosome);
	Creature();

	Chromosome GetChromosome() const;
	unsigned int GetFitness() const;

	std::vector<Chromosome> Crossover(Creature mate,float crossover);
};

struct CreatureLessThan
{
	bool operator()(const Creature& c1,const Creature& c2) const {
		int c1_fitness = c1.GetFitness();
		int c2_fitness = c2.GetFitness();

		return (c1_fitness < c2_fitness);
	}
};

#endif // CREATURE_H