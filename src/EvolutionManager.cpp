#include "EvolutionManager.h"


//! Constructor that get the setting from SettingsManager
/*! Creates a new evolution object and get the max generations
	from SettingsManager. 
*/
EvolutionManager::EvolutionManager(){
	SettingsManager *sm; 
    sm = SettingsManager::Instance();

	max_generations_ = sm->getMaxGenerations();

	ev_ = new Evolution(); //hmm, kommer göra så att all evolution kommer alltid att utgå från settingsklassen.
}

//! Destructor
EvolutionManager::~EvolutionManager(void){
	delete ev_;
}

//! Start the whole evolutionprocess until max generations
/*! Creates a random population and then starts to evolve
	the population to a new generation until max generation.
*/
void EvolutionManager::startEvolutionProcess() {
	std::clock_t start_time, time2; 
	start_time = std::clock();

	int max_gen = SettingsManager::Instance()->getMaxGenerations();

	// Creates a new random population
	Population population; 

	int i=0;
	Creature best = population.GetBest(); 

	// stores the first generation 
	allPopulations_.push_back(population);
	bestCreatures_.push_back(best); 

	while( (++i < max_gen) ) {
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

//! Prints the fitness value for the best creature in all different generations. 
void EvolutionManager::printBestFitnessValues(){
	for(int i=0; i<bestCreatures_.size(); i++){
		std::cout << "🐛" << "Generation " << i+1 << ". Best fitness: " << bestCreatures_[i].GetFitness() << std::endl; 
	}

}

//! Returns the best creature from the specified generation
/*! \param generation From which generation the best creature should be returned.
*/
Creature EvolutionManager::getBestCreatureFromGeneration(int generation){
	// must check if the value is smaller than max_generations, if over return the creature from last generation?
	if (generation<=max_generations_ && generation>0)
		return bestCreatures_[generation-1];

	return bestCreatures_.back(); 
}

//! Returns the best creature from the last generation. 
Creature EvolutionManager::getBestCreatureFromLastGeneration(){
	return bestCreatures_.back(); // inte säker metod då den kan vara tom.. 
}
