#include "Creature.h"

AutoInitRNG Creature::rng_;

Creature::Creature(Chromosome chromosome) : 
	chromosome_(chromosome) ,
	fitness_(CalculateFitness(chromosome_)){}

Creature::Creature() : 
	chromosome_(Chromosome()) ,
	fitness_(CalculateFitness(chromosome_)) {}

Chromosome Creature::GetChromosome() const{
	return chromosome_;
}

float Creature::GetFitness() const{
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
float Creature::CalculateFitness(Chromosome chromosome){
	float fitness = 0.0f;
	/*
	for (int i = 0; i < chromosome.GetGene().size(); ++i) {
		fitness += abs(((int) chromosome.GetGene()[i]) - ((int) Chromosome::TARGET_[i]));
	}
	*/

	/*
	for (int i = 0; i < chromosome.GetGene().size(); ++i){
		fitness += chromosome.GetGene()[i];
	}
	*/

	Simulation sim(chromosome.GetGene());
	for (int i = 0; i < 20*60*10; ++i){
		sim.step();
	}
	fitness = sim.getFitnessValue();
	return fitness;
}