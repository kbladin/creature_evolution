#include "Creature.h"
#include <cmath>
#include <ctime>
AutoInitRNG Creature::rng_;

// testningssyfte!!!
const char Creature::TARGET_[] = "Hello, world!";

Creature::Creature(std::string gene_code){
	gene_code_ = gene_code;
	fitness_ = CalculateFitness(gene_code); 
}

Creature::Creature(){
	gene_code_ = "Hello, debug!"; // bara för detta exempel! 
	fitness_ = 9999;
}

// new gene should always calulate the new fitness. 
void Creature::updateGene(std::string gene_code) {
	gene_code_ = gene_code;
	fitness_ = CalculateFitness(gene_code); 
}

std::string Creature::GetGene() const{
	return gene_code_;
}

unsigned int Creature::GetFitness() const{
	return fitness_;
}

std::vector<Creature> Creature::Crossover(Creature mate, float crossover){

	// generate a random number between 0 and 1
	std::uniform_real_distribution<float> crossover_decider(0,1);

	std::vector<Creature> children;
	
	// depends on the crossover rate, should we mate or not
	if (crossover_decider(rng_.mt_rng_) <= crossover) {

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
		
		children.push_back(child_1);
		children.push_back(child_2);

		return children;
	}

	Creature this_creature(gene_code_); // to return the thic creatures

	children.push_back(this_creature);
	children.push_back(mate);

	// should return the parents if not mated
	return children; 
}


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
}

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
}

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
}

// är beroeden på vad vi vill ha för fitnesscriteria, vår simulering. 
unsigned int Creature::CalculateFitness(std::string gene_code){
	int fitness = 0;
	for (int i = 0; i < gene_code.size(); ++i) {
		fitness += abs(((int) gene_code[i]) - ((int) TARGET_[i]));
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

	Creature random(random_gene);
	return random;
}
