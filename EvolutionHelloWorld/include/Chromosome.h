#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "AutoInitRNG.h"
#include <iostream>
#include <string>

class Chromosome {
public:
	Chromosome(std::string gene_code);
	Chromosome();

	std::string GetGene();
	void Mutate(float mutation);
	std::vector<Chromosome> CrossOverMate(Chromosome c);

private:
	std::string gene_code_;

	static AutoInitRNG rng_;
};

#endif // CHROMOSOME_H