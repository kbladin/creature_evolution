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

// new gene should always calulate the new fitness. 
void Creature::updateGene(Chromosome chromosome) {
	chromosome_ = chromosome;
	fitness_ = CalculateFitness(chromosome); 
}

Chromosome Creature::GetGene() const{
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

		std::uniform_int_distribution<int> int_dist_index_(0,chromosome_.GetGene().size()-1);

		int pivot_point = int_dist_index_(rng_.mt_rng_);

		std::string child_1_gene;
		std::string child_2_gene;

		child_1_gene = chromosome_.GetGene().substr(0,pivot_point);
		child_1_gene.append(mate.GetGene().GetGene(),pivot_point,
			mate.GetGene().GetGene().size());

		child_2_gene = mate.GetGene().GetGene().substr(0, pivot_point);
		child_2_gene.append(chromosome_.GetGene(),pivot_point, chromosome_.GetGene().size());

		Chromosome child_1(child_1_gene);
		Chromosome child_2(child_2_gene);

		//Creature child_1(child_1_gene);
		//Creature child_2(child_2_gene);
		
		children.push_back(child_1);
		children.push_back(child_2);

		return children;
	}

	//Creature this_creature(gene_code_); // to return this creatures

	children.push_back(chromosome_);
	children.push_back(mate.GetGene());

	// should return the parents if not mated
	return children; 
}

/*
// för att ha kvar den gamla!
std::vector<Creature> Creature::Mate(Creature mate){

	std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);

	int pivot_point = int_dist_index_(rng_.mt_rng_);

	std::string child_1_gene;
	std::string child_2_gene;

	child_1_gene = gene_code_.substr(0,pivot_point);
	child_1_gene.append(mate.GetGene(),pivot_point,
		mate.GetGene().size());

	child_2_gene = mate.GetGene().substr(0, pivot_point);
	child_2_gene.append(gene_code_,pivot_point, gene_code_.size());

	Creature child_1(child_1_gene);
	Creature child_2(child_2_gene);
		
	std::vector<Creature> children;
	children.push_back(child_1);
	children.push_back(child_2);
	
	return children;
}*/
/*
Creature Creature::MixMate(Creature mate) const{
	std::uniform_int_distribution<int> int_dist_index_(0,1);
	
	std::string new_gene = gene_code_;
  for (int i = 0; i < new_gene.length(); ++i){
    if (int_dist_index_(rng_.mt_rng_)){
      new_gene[i] = mate.GetGene()[i];
    }
  }

  Creature child(new_gene);
  return child;
}*/
/*
void Creature::Mutate(float mutation){
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
		updateGene(new_gene);
	}


}

// för att ha kvar den gamla funktionen
Creature Creature::Mutate() const{

	std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);
	std::uniform_int_distribution<int> int_dist_ascii_(32,126); //ascii 32-126
		
	int index_to_flip = int_dist_index_(rng_.mt_rng_);
	int random_character = int_dist_ascii_(rng_.mt_rng_);

	std::string new_gene = gene_code_;
	new_gene[index_to_flip] = (char) random_character;

	Creature mutated(new_gene);
	return mutated;
}*/

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
