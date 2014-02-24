#ifndef CREATURE_H
#define CREATURE_H

#include "AutoInitRNG.h"
#include <iostream>
#include <string>

class Creature {
private:
	std::string gene_code_;

	unsigned int fitness_; 
	static const char TARGET_[];
	static unsigned int CalculateFitness(std::string gene_code);
	static AutoInitRNG rng_;

public:
	// Constructor, one that will define the gene_code and one random
	Creature(std::string gene_code);
	Creature();

	std::string GetGene();
	unsigned int GetFitness() const;

	std::vector<Creature> Mate(Creature mate);
	Creature Mutate() const; 

	static Creature random();

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