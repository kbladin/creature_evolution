// GAHelloWorld.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <ctime>
#include "Chromosome.h"
#include "Population.h"
#include <iostream>
int main()
{
	const int population_size = 2048;
	const int max_generations = 16384;
	const float crossover_ratio = 0.8f;
	const float elitism_ratio = 0.2f;
	const float mutation_ratio = 0.5f;
	std::clock_t start_time;
	start_time = std::clock();
	Population pop(population_size, crossover_ratio,
							elitism_ratio, mutation_ratio);
	int i = 0;
	Chromosome best = pop.GetChromosomes()[0];

	while((i++ <= max_generations) && (best.GetFitness() != 0)) {
		std::cout << "Generation " << i << ": " << best.GetGene() << std::endl;
		pop.Evolve();
		best = pop.GetChromosomes()[0];
	}

	std::cout << "Generation " << i << ": " << best.GetGene() << std::endl;


	std::cout << "Total time: " << std::clock() -start_time << 
			" ms" << std::endl;
	return 0;
}

