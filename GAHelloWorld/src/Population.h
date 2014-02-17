#ifndef POPULATION_H
#define POPULATION_H

#include "AutoInitRNG.h"
#include "Chromosome.h"
#include <vector>

class Population
{
private:
	const static int TOURNAMENT_SIZE_ = 3;

	float elitism_;
	float mutation_;
	float crossover_;

	std::vector<Chromosome> chromosome_population_;
	std::vector<Chromosome> SelectParents();

	static AutoInitRNG rng_;

public:
	Population(int size, float crossover_ratio, float elitism_ratio,
				float mutation_rate);
	~Population(void);

	void Evolve();
	std::vector<Chromosome> GetChromosomes();
	float GetElitism();
	float GetCrossover();
	float GetMutation();
};

#endif // POPULATION_H

