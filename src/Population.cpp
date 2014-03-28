#include "Population.h"

//! A constructor that creates a whole new random population
/*! Gets the population size from the SettingsManager. 
	Creates a random population filled with creatures as 
	many as population size. Then sorts the vector depending
	on the fitness value of each creature. 
*/
Population::Population() {
	//get the populationsize from settingsmanager
	population_size_ = SettingsManager::Instance()->GetPopulationSize();
	pop_.resize(population_size_);

	// fill with random creatures
	for (int i=0; i<population_size_; i++) {
		pop_[i] = Creature(Chromosome::random());
	}

	Sort();
}

//! A constructor that will copy over some creatures from the oldPopulation
/*! Copy over the population based on the pivot from the oldPopulation. 
*/
Population::Population(int pivot, const Population &oldPopulation){
	population_size_ = SettingsManager::Instance()->GetPopulationSize();
	pop_.resize(population_size_);

	for (int i=0; i<pivot; i++) {
		pop_[i] = oldPopulation.Get(i);
	}

	Sort();

}

//! Adds a creature to the population on the index that is specified. 
/*! \param index Where the creature should be added.
	\c The creature that should be added to the population. 
*/
void Population::Add(int index, Creature c){
	if (index < population_size_){
		pop_[index] = c; 
	}
}

//! Sort the population based on the creatures fitness value.
void Population::Sort() {
	std::sort(pop_.begin(), pop_.end(), CreatureLargerThan() );
}

//! Returns the creature at the position index. 
Creature Population::Get(int index) const{
	// TODO: check if valid index!
	return pop_[index]; 

}

Creature Population::GetBest() const{
	//TODO: check if a population exist maybe?
	return pop_[0]; 
}

int Population::size() const{
	return population_size_; 
}