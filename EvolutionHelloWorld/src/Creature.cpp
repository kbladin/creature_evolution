#include "Creature.h"
#include <cmath>
#include <ctime>
AutoInitRNG Creature::rng_;

// testningssyfte!!!
const char Creature::TARGET_[] = "Hello, world!";

Creature::Creature(Chromosome chromosome){
	chromosome_ = chromosome;
	fitness_ = CalculateFitness(chromosome); 
}

Creature::Creature(){
	chromosome_ = Chromosome("Hello, debug!"); // bara för detta exempel! 
	fitness_ = 9999;
}

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
		fitness += abs(((int) chromosome.GetGene()[i]) - ((int) TARGET_[i]));
	}
	return fitness;
}

Creature Creature::random() {
	std::string target = TARGET_; 
	int random_gene_size = target.size();
	std::uniform_int_distribution<int> int_dist_ascii_(32,126);

	std::string random_gene;
	random_gene.resize(random_gene_size);

	for (int i = 0; i < random_gene_size; ++i) {
		
		random_gene[i] = (char) int_dist_ascii_(rng_.mt_rng_);
	}


	Chromosome random_chromosom(random_gene); 
	
	Creature random(random_chromosom);
	return random;
}
