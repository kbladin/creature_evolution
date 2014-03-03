#include "Creature.h"
#include <cmath>
#include <ctime>
AutoInitRNG Creature::rng_;

Creature::Creature(Chromosome chromosome) : 
	chromosome_(chromosome) ,
	fitness_(CalculateFitness(chromosome_)){}

Creature::Creature() : 
	chromosome_(Chromosome("Hello, debug!")) ,
	fitness_(CalculateFitness(chromosome_)) {}

Chromosome Creature::GetChromosome() const{
	return chromosome_;
}

unsigned int Creature::GetFitness() const{
	return fitness_;
}

std::vector<Chromosome> Creature::Crossover(Creature mate, float crossover){

	// generate a random number between 0 and 1
	std::uniform_real_distribution<float> crossover_decider(0,1);

	std::vector<Chromosome> children;
	
	// depends on the crossover rate, should we mate or not
	if (crossover_decider(rng_.mt_rng_) <= crossover) {
		children = chromosome_.CrossOverMate(mate.GetChromosome());
		return children;
	}

	//Creature this_creature(gene_code_); // to return this creatures
	children.push_back(chromosome_);
	children.push_back(mate.GetChromosome());

	// should return the parents if not mated
	return children; 
}

// är beroeden på vad vi vill ha för fitnesscriteria, vår simulering. 
unsigned int Creature::CalculateFitness(Chromosome chromosome){
	int fitness = 0;
	for (int i = 0; i < chromosome.GetGene().size(); ++i) {
		fitness += abs(((int) chromosome.GetGene()[i]) - ((int) Chromosome::TARGET_[i]));
	}
	return fitness;
}
