#include "Chromosome.h"

AutoInitRNG Chromosome::rng_;

//! Creates a chromosome with the given gene code.
/*!	
	\param gene_code a vector of floats. 
*/
Chromosome::Chromosome(std::vector<float> gene_code){
	gene_code_ = gene_code;
}


//! Creates a random gene code to the chromosome. 
Chromosome::Chromosome(){
	gene_code_ = std::vector<float>(GENE_LENGTH);
	for (int i = 0; i < GENE_LENGTH; ++i) {
		gene_code_[i] = 0.0f;
	}
}


//! Returnes the gene code
/*!	
	\return A vector of floats
*/
std::vector<float> Chromosome::GetGene() const{
	return gene_code_; 
}


//! Mutate a random gene in the chromosome based on the mutation ratio
/*!	
	Mutate a random selected gene given by the mutation ratio.

	\param mutation The mutation ratio thah gives the odds if a gene will mutate. 
*/
void Chromosome::Mutate(float mutation){
	std::uniform_real_distribution<float> crossover_decider(0,1);

	if (crossover_decider(rng_.mt_rng_) <= mutation) {

		std::uniform_int_distribution<int> int_dist_index(0,gene_code_.size()-1);
		std::uniform_real_distribution<float> float_dist_param(0,1);
		
		int index_to_flip = int_dist_index(rng_.mt_rng_);
		float random_parameter = float_dist_param(rng_.mt_rng_);

		gene_code_[index_to_flip] = random_parameter;
	}
}


//! Crossover two chromosome with eachother. (Mate two parents)
/*!	

	Mate two parents and get two children. Slips the parents on
	a random generated pivot point. Child 1 get first half from parent 1
	and second half from parent 2 and Child 2 the other way around.  

	\param mate The chromosome that will be mated with
	\return A vector of the two new chromosome that are mated (the children)
*/
std::vector<Chromosome> Chromosome::CrossOverMate(const Chromosome mate){
	std::uniform_int_distribution<int> int_dist_index(0, gene_code_.size()-1);

	int pivot_point = int_dist_index(rng_.mt_rng_);

	std::vector<float> gene_code_mate = mate.GetGene();

	std::vector<float> child_1_gene(gene_code_.begin(), gene_code_.begin() + pivot_point);
	child_1_gene.insert( child_1_gene.end(), gene_code_mate.begin() + pivot_point, gene_code_mate.end());
	
	std::vector<float> child_2_gene(gene_code_mate.begin(), gene_code_mate.begin() + pivot_point);
	child_2_gene.insert( child_2_gene.end(), gene_code_.begin() + pivot_point, gene_code_.end());

	Chromosome child_1(child_1_gene);
	Chromosome child_2(child_2_gene);

	std::vector<Chromosome> children;
	children.push_back(child_1);
	children.push_back(child_2);

	return children;	
}


//! Returns a random created chromosome (random genes).
Chromosome Chromosome::random(){
	std::uniform_real_distribution<float> float_dist_param(0,1);
	std::vector<float> random_gene_code(GENE_LENGTH);

	for (int i = 0; i < GENE_LENGTH; ++i){
		random_gene_code[i] = float_dist_param(rng_.mt_rng_);
	}

	Chromosome random(random_gene_code);

	return random;
}