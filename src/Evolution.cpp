#include "Evolution.h"

AutoInitRNG Evolution::rng_;

//! Creates a evolution and stores the arguments.
/*!
	Stores the arguments for a evolution so that every generation 
	will get the same constants.

\param crossover_ratio How likely the creatures will crossover (mate)
\param elitism_ratio How many creatures that will be transfered to the new generation.
\param mutation_ratio The odds of the mutation of the genes.
*/
Evolution::Evolution(float crossover_ratio, float elitism_ratio, 
		float mutation_ratio){
	
	crossover_ = crossover_ratio;
	elitism_ = elitism_ratio;
	mutation_ = mutation_ratio;
}

//! Constructor that reads from the SettingsManager class. 
Evolution::Evolution(){ 

    SettingsManager *sm; 
    sm = SettingsManager::Instance();

	crossover_ = sm->getCrossover();
	elitism_ = sm->getElitism();
	mutation_ = sm->getMutation();
}

//! A destructor
Evolution::~Evolution(void){
}


//! Get the population and evolve the generation to get a new population. 
/*! 
	Take a generation (a population) we want to evolve to get the next generation from. 

\param population The population we want to get a new generation from.
\return A population is returned with the new creatures that have survived, borned and evolved..
*/
Population Evolution::nextGeneration(const Population &population ) {

	int top_candidates_pivot = (int) (population.size() * elitism_);

	// Copy over the top candidates to the new population
	Population buffer(top_candidates_pivot, population);

	//int count_new_population = top_candidates_pivot;

	//while(count_new_population < population.size()-1){

	for(int index = top_candidates_pivot; index < population.size() - 1; ++index){

		std::vector<Creature> parents = TournamentSelection(population);

		std::vector<Chromosome> children_chromosome = parents[0].Crossover(parents[1], crossover_);

		children_chromosome[0].Mutate(mutation_);
		children_chromosome[1].Mutate(mutation_); 

		Creature child_1(children_chromosome[0]);
		Creature child_2(children_chromosome[1]);

		buffer.Add(index, child_1);
		index+=1;
		buffer.Add(index, child_2);
	}
	return buffer; 
}

//! Private class function that helps to select the best cretures in the population. 
/*!

The function uses the algorithm Tournament selection. It is running several "tournaments"
among the creatures from the population. The winner of each tournament (the one with best fitness)
is selected to be a parent (and maybe later use to crossover). The selection pressure is adjusted 
by changing the TOURNAMENT_SIZE_. 

\param population The population that we pick random creatures from to compete in the tournament. 
\return A new population with the two parents.
*/
std::vector<Creature> Evolution::TournamentSelection(const Population &population) {
	std::vector<Creature> parents;
	parents.resize(2);
	std::uniform_int_distribution<int> int_dist_index_(0,
						population.size()-1);

	for (int i = 0; i < 2; ++i) {
		parents[i] = population.Get(int_dist_index_(rng_.mt_rng_));
		for (int j = 0; j < TOURNAMENT_SIZE_; ++j) {
			int idx = int_dist_index_(rng_.mt_rng_);
			if(population.Get(idx).GetFitness() > 
										parents[i].GetFitness()) {
				parents[i] = population.Get(idx);
			}
		}
	}

	return parents;
}

//! Private class function that helps to select the best creatures in the population. 
/*!
	Uses the algorithm roulette. Selects a creature from the population via wheel selection.
	Each creature has "slice" that is proportional to the fitness. Better fitness, higher
	chance to be choosen. 

	NOTE: this algoritm take a litte more time to go through..

\param population The population that we pick random creatures from
\param total_fitness Total fitness of the population. May be calculated by function CalculateTotalFitness. 
\return A new population with the two parents.
*/
Creature Evolution::Roulette(float total_fitness, const Population &population){
	std::uniform_real_distribution<float> float_dist_index_(0,total_fitness);
	float slice = float_dist_index_(rng_.mt_rng_);

	float fitness_so_far = 0.0f;

	for (int i=0; i<population.size(); ++i){
		if (population.Get(i).GetFitness() != 0)
			fitness_so_far += 1/population.Get(i).GetFitness();

		if (fitness_so_far >= slice)
			return population.Get(i); 
	}

	// should have gone trought the whole list, but if not the first object is returned
	return population.Get(0); 
}

//! Help to the Roulette function
/*!

	Calculates the whole fitness in the population in order to get the "slices"
	correct size in Roulette function. 
\return The total fitness of the whole population.
*/
float Evolution::CalculateTotalFitness(const Population &population){
	float total_fitness = 0.0f;

	for (int i=0; i<population.size(); ++i) {
		total_fitness += population.Get(i).GetFitness();
	}

	return total_fitness; 
}
