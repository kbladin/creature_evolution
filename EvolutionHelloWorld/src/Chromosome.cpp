#include "Chromosome.h"

AutoInitRNG Chromosome::rng_;

Chromosome::Chromosome(std::string gene_code){
	gene_code_ = gene_code;
}

Chromosome::Chromosome(){
	gene_code_ = "Hello debug";
}

std::string Chromosome::GetGene(){
	return gene_code_; 
}

void Chromosome::Mutate(float mutation){
	// generate a random number between 0 and 1
	std::uniform_real_distribution<float> crossover_decider(0,1);

	// if we should mutate or not. 
	if (crossover_decider(rng_.mt_rng_) <= mutation) {

		std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);
		std::uniform_int_distribution<int> int_dist_ascii_(32,126); //ascii 32-126
		
		int index_to_flip = int_dist_index_(rng_.mt_rng_);
		int random_character = int_dist_ascii_(rng_.mt_rng_);

		std::string new_gene = gene_code_;
		new_gene[index_to_flip] = (char) random_character;

		// change this cretures gene and fitness code
		gene_code_ = new_gene; 
	}


}