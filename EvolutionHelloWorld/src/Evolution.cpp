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

	// creates where the new population will be
	std::vector<Creature> buffer (&population[0], 
		&population[top_candidates_pivot]);
	buffer.resize(population.size());

	int count_new_population = top_candidates_pivot;

	while(count_new_population < population.size()-1){

		std::vector<Creature> parents = SelectParents(population);

		// mate the "parents" if crossover_ratio low, take the parents instead.
		std::vector<Creature> children = parents[0].Crossover(parents[1], crossover_);

		// mutate the children?
		children[0].Mutate(mutation_);
		children[1].Mutate(mutation_);  

		// add to the buffer.
		buffer[count_new_population++] = children[0];
		buffer[count_new_population++] = children[1];
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

// Private class function. help to select the best parents
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
// 	better fitness, higher chance to go trough but the best creature can die..
// 	NOTE: take more time to go trough. så maybe not so good. 
Creature Evolution::Roulette(float total_fitness, const std::vector<Creature> &population){
	// generate a random number between 0 & total_fitness
	std::uniform_real_distribution<float> float_dist_index_(0,total_fitness);
	float slice = float_dist_index_(rng_.mt_rng_);

	//go through the creatures adding up the fitness so far
	float fitness_so_far = 0.0f;

	for (int i=0; i<population.size(); ++i){
		if (population[i].GetFitness() != 0)
			fitness_so_far += 1/population[i].GetFitness();

		if (fitness_so_far >= slice)
			return population[i]; 
	}

// should have gone trought the whole list, but if not the first object is returned
	return population[0]; 
}

// Help function in roulette. 
float Evolution::CalculateTotalFitness(const std::vector<Creature> &population){
	float total_fitness = 0.0f;

	for (int i=0; i<population.size(); ++i) {
		total_fitness += population[i].GetFitness();
	}

	return total_fitness; 
}



