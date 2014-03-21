#include "EvolutionManager.h"


//! Constructor
EvolutionManager::EvolutionManager(){
	std::cout << "Created EvolutionManager." << std::endl;

	SettingsManager *sm; 
    sm = SettingsManager::Instance();

	max_generations_ = sm->getMaxGenerations();
	//population_size_ = sm->getPopulationSize();

	ev_ = new Evolution(); //hmm, kommer göra så att all evolution kommer alltid att utgå från settingsklassen.
}

//! Destructor
EvolutionManager::~EvolutionManager(void){
	delete ev_;
}

// an evoultion until max generation
void EvolutionManager::startEvolutionProcess() {
	std::clock_t start_time, time2; 
	start_time = std::clock();

	// Creates a new random population
	Population population; 

	int i=0;
	Creature best = population.GetBest(); 

	// stores the first generation 
	allPopulations_.push_back(population);
	bestCreatures_.push_back(best); 

	while( (++i < max_generations_) ) {
		time2 = std::clock();

		population = ev_->nextGeneration(population);
		population.Sort();
		best = population.GetBest();

		// save the population and the best creatures
		allPopulations_.push_back(population);
		bestCreatures_.push_back(best); 

		std::cout << "Generation " << i << std::endl;

		//std::cout << "Simulation for an evolution:" << float(std::clock() - time2) / CLOCKS_PER_SEC << " s" << std::endl;  
	}

	std::cout << "Total simulation time: " << float(std::clock() - start_time) / CLOCKS_PER_SEC  << " s" << std::endl;

}

void EvolutionManager::printBestFitnessValues(){
	for(int i=0; i<bestCreatures_.size(); i++){
		std::cout << "🐛" << "Generation " << i+1 << ". Best fitness: " << bestCreatures_[i].GetFitness() << std::endl; 
	}

}

Creature EvolutionManager::getBestCreatureFromGeneration(int generation){
	// must check if the value is smaller than max_generations, if over return the creature from last generation?
	if (generation<=max_generations_ && generation>0)
		return bestCreatures_[generation-1];

	return bestCreatures_.back(); 
}

// bara för test! för att det ska funka nu helt enkelt. 
Creature EvolutionManager::getBestCreatureFromLastGeneration(){
	return bestCreatures_.back(); // inte säker metod då den kan vara tom.. 
}
