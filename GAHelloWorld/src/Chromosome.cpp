#include "Chromosome.h"
#include <cmath>
#include <ctime>
const char Chromosome::TARGET_[] = "Hello, world!";
AutoInitRNG Chromosome::rng_;

Chromosome::Chromosome() {
	gene_code_ = "Hello, debug!";
	fitness_ = 9999;
}

Chromosome::Chromosome(std::string code) {
	gene_code_ = code;
	fitness_ = CalculateFitness(code);
}

std::string Chromosome::GetGene() {
	return gene_code_;
}

unsigned int Chromosome::GetFitness() const{
	return fitness_;
}

unsigned int Chromosome::CalculateFitness(std::string code) {
	int fitness = 0;
	for (int i = 0; i < code.size(); ++i) {
		fitness += abs(((int) code[i]) - ((int) TARGET_[i]));
	}
	return fitness;
}

void Chromosome::SetGene(std::string debug_string) {
	gene_code_ = debug_string;
}

Chromosome Chromosome::Mutate() {
	std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);
	std::uniform_int_distribution<int> int_dist_ascii_(32,126); //ascii 32-126
	
	int index_to_flip = int_dist_index_(rng_.mt_rng_);
	int random_character = int_dist_ascii_(rng_.mt_rng_);

	std::string new_gene = gene_code_;
	new_gene[index_to_flip] = (char) random_character;

	Chromosome mutated(new_gene);
	return mutated;
}

std::vector<Chromosome> Chromosome::Mate(Chromosome mate) {
	
	std::uniform_int_distribution<int> int_dist_index_(0,gene_code_.size()-1);

	int pivot_point = int_dist_index_(rng_.mt_rng_);

	std::string child_1_gene;
	std::string child_2_gene;

	child_1_gene = gene_code_.substr(0,pivot_point);
	child_1_gene.append(mate.GetGene(),pivot_point,
		mate.GetGene().size());

	child_2_gene = mate.GetGene().substr(0, pivot_point);
	child_2_gene.append(gene_code_,pivot_point, gene_code_.size());


	Chromosome child_1(child_1_gene);
	Chromosome child_2(child_2_gene);

	std::vector<Chromosome> children;
	children.push_back(child_1);
	children.push_back(child_2);

	return children;
}

Chromosome Chromosome::random() {
	std::string target = "Hello, world!";
	int random_gene_size = target.size();
	std::uniform_int_distribution<int> int_dist_ascii_(32,126);

	std::string random_gene;
	random_gene.resize(random_gene_size);

	for (int i = 0; i < random_gene_size; ++i) {
		
		random_gene[i] = (char) int_dist_ascii_(rng_.mt_rng_);
	}

	Chromosome random(random_gene);
	return random;
}
