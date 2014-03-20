#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "AutoInitRNG.h"
#include <iostream>
#include <iomanip>
#include <string>

//! A chromosome that a creature contains of. 

class Chromosome {
public:
	Chromosome(std::vector<float> gene_code);
	Chromosome();

	std::vector<float> GetGene() const;
	void Mutate(float mutation);
	std::vector<Chromosome> CrossOverMate(const Chromosome c);

	static Chromosome random();

	static const int GENE_LENGTH = 16; //Worm length * 4 - 1

private:
	std::vector<float> gene_code_;
	static AutoInitRNG rng_;
};

static std::ostream& operator<<(std::ostream& os, const Chromosome c){
	for (int i = 0; i < c.GetGene().size(); ++i){
		os << std::setprecision(3) << c.GetGene()[i] << " ";  
	}
    return os;
}

static std::ostream& operator<<(std::ostream& os, const std::vector<float> c){
	for (int i = 0; i < c.size(); ++i){
		os << std::setprecision(3) << c[i] << " ";  
	}
    return os;
}

#endif // CHROMOSOME_H