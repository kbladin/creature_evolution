#include "Evolution.h"

AutoInitRNG Evolution::rng_;

Evolution::Evolution(float crossover_ratio, float elitism_ratio, 
		float mutation_ratio){
	
	crossover_ = crossover_ratio;
	elitism_ = elitism_ratio;
	mutation_ = mutation_ratio;
}

Evolution::~Evolution(void){
}


std::vector<Creature> Evolution::nextGeneration(const std::vector<Creature> &population ) {
	int top_candidates_pivot = (int) (population.size() * elitism_);
	std::uniform_real_distribution<float> crossover_decider(0,1);

	// copy over the top candidates to a buffer
	std::vector<Creature> buffer (&population[0], 
		&population[top_candidates_pivot]);
	buffer.resize(population.size()); // make it as big as the population to fill later


	// fyll på creature så länge det finns plats i buffern.
	while (top_candidates_pivot < buffer.size() - 1) {
		if(crossover_decider(rng_.mt_rng_) <= crossover_) {
			std::vector<Creature> parents = SelectParents(population);
			std::vector<Creature> children = parents[0].Mate(parents[1]);

			if(crossover_decider(rng_.mt_rng_) <= mutation_) {
				buffer[top_candidates_pivot+1] = children[0].Mutate();
			} else {
				buffer[top_candidates_pivot+1] = children[0];
			}

			if(top_candidates_pivot < buffer.size()) {
				if(crossover_decider(rng_.mt_rng_) <= mutation_) {
					buffer[top_candidates_pivot] = children[1].Mutate();
				} else {
					buffer[top_candidates_pivot] = children[1];
				}
			}
		} else {
			if(crossover_decider(rng_.mt_rng_) <= mutation_) {
				buffer[top_candidates_pivot] = 
						population[1].Mutate();
			} else {
				buffer[top_candidates_pivot] = population[1];
			}
		}

		++top_candidates_pivot;
	}


	return buffer; 
}

void Evolution::nextGenerationMixedMating( std::vector<Creature> &population ){
  int top_candidates_pivot = (int) (population.size() * elitism_);
  std::vector<Creature> parents (&population[0], 
  	&population[top_candidates_pivot]);
  //std::vector<Creature> child_buffer(population.size());

  //First do the mating of the top candidates and put the children in a new vector
  std::uniform_int_distribution<int> parents_decider(0,top_candidates_pivot-1);
  for (int i = 0; i < population.size(); ++i){
    //Pick parents from among the "best" (left side of pivot)
    Creature firstParent = parents[parents_decider(rng_.mt_rng_)];
    Creature secondParent = parents[parents_decider(rng_.mt_rng_)];
    population[i] = firstParent.Mate(secondParent)[0];
  }

  //Then mutate them poor bastards
  std::uniform_real_distribution<float> mutation_decider(0,1);
  for (int i = 0; i < population.size(); ++i){
    if (mutation_decider(rng_.mt_rng_) <= mutation_){
      population[i] = population[i].Mutate();
    }
  }  

}

// private class function. help to select the best parents
std::vector<Creature> Evolution::SelectParents(const std::vector<Creature> &population) {
	std::vector<Creature> parents;
	parents.resize(2);
	std::uniform_int_distribution<int> int_dist_index_(0,
						population.size()-1);

	for (int i = 0; i < 2; ++i) {
		parents[i] = population[int_dist_index_(rng_.mt_rng_)];
		for (int j = 0; j < TOURNAMENT_SIZE_; ++j) {
			int idx = int_dist_index_(rng_.mt_rng_);
			if(population[idx].GetFitness() < 
										parents[i].GetFitness()) {
				parents[i] = population[idx];
			}
		}
	}

	return parents;
}