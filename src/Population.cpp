#include "Population.h"

// konstruktor
Population::Population() {
	//get the populationsize from settingsmanager
	population_size_ = SettingsManager::Instance()->getPopulationSize();
	pop_.resize(population_size_);

	// fill with random creatures
	for (int i=0; i<population_size_; i++) {
		pop_[i] = Creature(Chromosome::random());
	}

	Sort();
}

// copy over the population based on the pivot
Population::Population(int pivot, const Population &oldPopulation){
	population_size_ = SettingsManager::Instance()->getPopulationSize();
	pop_.resize(population_size_);

	for (int i=0; i<pivot; i++) {
		pop_[i] = oldPopulation.Get(i);
	}

	Sort();

}

// add a creature if index is less than population size
void Population::Add(int index, Creature c){
	if (index < population_size_){
		pop_[index] = c; 
	}
}

void Population::Sort() {
	std::sort(pop_.begin(), pop_.end(), CreatureLargerThan() );
}


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