#ifndef CREATURE_H
#define CREATURE_H

#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

#include "Simulation.h"
#include "Chromosome.h"
#include "AutoInitRNG.h"

//! A definition of a creature.

/*!
A creature contains of a chromosome and a fitness value. 
*/

class Creature {
private:
	Chromosome chromosome_;

	float fitness_; 
	static float CalculateFitness(Chromosome chromsome);
	static AutoInitRNG rng_;

public:
	// Constructor, one that will define the gene_code and one random
	Creature(Chromosome cromosome);
	Creature();

	Chromosome GetChromosome() const;
	float GetFitness() const;

	std::vector<Chromosome> Crossover(Creature mate,float crossover);
};

struct CreatureLargerThan
{
	bool operator()(const Creature& c1,const Creature& c2) const {
		float c1_fitness = c1.GetFitness();
		float c2_fitness = c2.GetFitness();

		return (c1_fitness > c2_fitness);
	}
};

static std::ostream& operator<<(std::ostream& os, const Creature c){
	for (int i = 0; i < c.GetChromosome().GetGene().size(); ++i){
		os << std::setprecision(3) << c.GetChromosome().GetGene()[i] << " ";  
	}
    return os;
}

#endif // CREATURE_H