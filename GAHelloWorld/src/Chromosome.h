#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "AutoInitRNG.h"
#include <iostream>
#include <string>

class Chromosome {
private:
	std::string gene_code_;
	unsigned int fitness_;
	static const char TARGET_[];
	static unsigned int CalculateFitness(std::string gene_code);
	static AutoInitRNG rng_;


public:
	Chromosome(std::string gene_code);
	Chromosome();

	std::string GetGene();
	unsigned int GetFitness() const;
	void SetGene(std::string debug_gene_code); //primarily for testing/debugging
	static bool Equals();
	
	Chromosome Mutate();
	std::vector<Chromosome> Mate(Chromosome mate);

	static Chromosome random();


	//functors

};

struct ChromosomeLessThan
{
	bool operator()(const Chromosome& c1,const Chromosome& c2) const {
		int c1_fitness = c1.GetFitness();
		int c2_fitness = c2.GetFitness();

		return (c1_fitness < c2_fitness);
	}
};

#endif // CHROMOSOME_H
