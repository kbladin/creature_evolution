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

std::vector<Creature> Evolution::nextGen(const std::vector<Creature> &population ) {

	// creates where the new population will be
	std::vector<Creature> buffer;
	buffer.resize(population.size());

	int count_new_population = 0;

	while(count_new_population < population.size()) {
		
	}


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

std::vector<Creature> Evolution::nextGenerationMixedMating( const std::vector<Creature> &population ){
  int top_candidates_pivot = (int) (population.size() * elitism_);
  std::vector<Creature> child_buffer(population.size());  

  //First do the mating of the top candidates and put the children in a new vector
  std::uniform_int_distribution<int> parents_decider(0,top_candidates_pivot-1);
  for (int i = 0; i < child_buffer.size(); ++i){
    //Pick parents from among the "best" (left side of pivot)
    Creature firstParent = population[parents_decider(rng_.mt_rng_)];
    Creature secondParent = population[parents_decider(rng_.mt_rng_)];
    child_buffer[i] = firstParent.MixMate(secondParent);
  }

  //Then mutate them poor bastards
  std::uniform_real_distribution<float> mutation_decider(0,1);
  for (int i = 0; i < child_buffer.size(); ++i){
    if (mutation_decider(rng_.mt_rng_) <= mutation_){
      child_buffer[i] = child_buffer[i].Mutate();
    }
  }  

  return child_buffer;
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

//	selects a creature from the population via roulette wheel selection
//  each creature has a "slice" that is proportional to the fitness.
// higher fitness, higher chance to go trough but the best creature can die..
// instead of select partens. 
Creature Evolution::Roulette(const std::vector<Creature> &population){
	// generate a random number between 0 & total_fitness
	float total_fitness = CalculateTotalFitness(population);
	std::uniform_real_distribution<float> float_dist_index_(0,total_fitness);
	float slice = float_dist_index_(rng.mt_rng_);

	//go through the creatures adding up the fitness so far
	float fitness_so_far = 0.0f;

	for (int i=0; i<population.size(); ++i){
		fitness_so_far += population[i].GetFitness();

		if (fitness_so_far >= slice)
			return population[i]; 
	}

// should have gone trought the whole list, but if not the first object is returned
	return population[0]; 
}


// Help function in roulette. 
float Evolution::CalculateTotalFitness(const std::vector<Creture> &population){
	float total_fitness = 0.0f;

	for (int i=0; i<population.size(); ++i) {
		total_fitness += population[i].GetFitness();
	}

	return total_fitness; 
}



