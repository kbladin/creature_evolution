#include "EvolutionManager.h"


//! Constructor
EvolutionManager::EvolutionManager(){
	std::cout << "Created EvolutionManager." << std::endl;

	SettingsManager *sm; 
    sm = SettingsManager::Instance();

	max_generations_ = sm->getMaxGenerations();
	population_size_ = sm->getPopulationSize();

	ev_ = new Evolution(); //hmm, kommer göra så att all evolution kommer alltid att utgå från settingsklassen.
}

//! Destructor
EvolutionManager::~EvolutionManager(void){
	delete ev_;
}

// an evoultion until max generation or if fitness goes above 30! (change later)
void EvolutionManager::startEvolutionProcess() {
	std::clock_t start_time;
	start_time = std::clock();

	// creates the population!
	std::vector<Creature> population;
	population.resize(population_size_);

	// creates a random new population
	for (int i=0; i<population_size_; ++i){
		population[i] = Creature(Chromosome::random());
	}

	// sortera Creature
	std::sort(population.begin(), population.end(), CreatureLargerThan());

	int i=0;
	Creature best = population[0]; // the best creature from the population
	
	// stores the first generation 
	allPopulations_.push_back(population);
	bestCreatures_.push_back(best); 

	while( (++i < max_generations_) && (best.GetFitness() < 30) ) {

		population = ev_->nextGeneration(population);
		std::sort(population.begin(), population.end(), CreatureLargerThan());
		best = population[0];

		// save the population and the best creatures
		allPopulations_.push_back(population);
		bestCreatures_.push_back(best); 
	}

	std::cout << "Simulation time: " << double( (std::clock() - start_time) / CLOCKS_PER_SEC ) << " s" << std::endl;

}

void EvolutionManager::printBestFitnessValues(){
	for(int i=0; i<bestCreatures_.size(); i++){
		std::cout << "🐛" << "Generation " << i+1 << ". Best fitness: " << bestCreatures_[i].GetFitness() << std::endl; 
	}

}

// bara för test! för att det ska funka nu helt enkelt. 
Creature EvolutionManager::getBestCreatureFromLastGeneration(){
	return bestCreatures_.back(); // inte säker metod då den kan vara tom.. 
}
