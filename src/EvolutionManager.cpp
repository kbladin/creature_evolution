#include "EvolutionManager.h"

AutoInitRNG EvolutionManager::rng_;

//! Constructor that get the setting from SettingsManager
/*! Creates a new evolution object and get the max generations
	from SettingsManager.
*/
EvolutionManager::EvolutionManager(){
}

//! Destructor
EvolutionManager::~EvolutionManager(void){
	//should delete all creatures
}

//! Start the whole evolutionprocess until max generations
/*! Creates a random population and then starts to evolve
	the population to a new generation until max generation.
*/
void EvolutionManager::startEvolutionProcess() {
	std::clock_t start_time, time2;
	start_time = std::clock();

	int max_gen = SettingsManager::Instance()->GetMaxGenerations();
	int pop_size = SettingsManager::Instance()->GetPopulationSize();

	std::cout << "Generation: " << 0 << std::endl <<
	"Simulating..." << std::endl;

	// Creates a new random population
	current_population_ = CreateRandomPopulation(pop_size);
	SimulatePopulation();
	CalculateFitnessOnPopulation();
	SortPopulation();

	Creature best = GetBestCreature();

	// stores the first generation
	best_creatures_.push_back(best);

	std::cout << "Done! Best fitness: " << best.GetFitness() << std::endl;

	for (int i = 1; i < max_gen; ++i){
		std::cout << "Generation: " << i << std::endl <<
		"Simulating..." << std::endl;

		time2 = std::clock();

		current_population_ = NextGeneration();
		SimulatePopulation();
		CalculateFitnessOnPopulation();
		SortPopulation();
		best = GetBestCreature();

		// save the population and the best creatures
		best_creatures_.push_back(best);

	}
	std::cout << "Total simulation time: " << float(std::clock() - start_time) / CLOCKS_PER_SEC  << " s" << std::endl;
}

//! Prints the fitness value for the best creature in all different generations.
void EvolutionManager::printBestFitnessValues(){
	for(int i=0; i<best_creatures_.size(); i++){
		std::cout << "🐛" << "Generation " << i+1 << ". Best fitness: " << bestCreatures_[i].GetFitness() << std::endl;
	}

}

//! Returns the best creature as of when this method is called
Creature EvolutionManager::GetBestCreature() {
	return current_population_[0];
}

//! Simulates all creatures in population
void EvolutionManager::SimulatePopulation() {
	Simulation sim_world;
	for(int i = 0; i < current_population_.size(); ++i) {
		world.AddCreature(current_population_[i]);
		world.Simulate();
		world.RemoveCreature();
	}
}

//! Calculates fitness values for all creatures in population by 
// looking at values stored during simulation
void EvolutionManager::CalculateFitnessOnGeneration() {
	float max_pos;
	float max_speed;
    for(Creature& creature in current_population_) {
		if(creature.GetPos() > max_pos)
			max_pos = creature.GetPos();
    }

	//normalize all creatures
    for(Creature& creature in current_population_) {
		float fitness = creature.GetPos()/max_pos;// + w2*creature.GetSpeed()/max_speed;
		creature.SetFitness(fitness);
    }
}

//! Sorts the current population based on fitness value. Should only be called once fitness
// values have been obtained
void EvolutionManager::SortPopulation() {
	std::sort(current_population_.begin(), current_population_.end(), CreatureLarger());
}


//! Evolves the current population based on simple mutation and elitism
void EvolutionManager::NextGeneration() {
	float elitism = SettingsManager::Instance()->GetElitism();
	float mutation = SettingsManager::Instance()->GetMutation();

	int elitism_pivot = (int) (current_population_.size() * elitism);

	Population new_population (&current_population_[0],
		 &current_population_[elitism_pivot]);

	new_population.resize(current_population_.size());
	std::uniform_int_distribution<int> int_elitism_index(0, elitism_pivot);

	for(int i = elitism_pivot; i < new_population.size(); ++i) {


		Creature new_creature = current_population_[int_elitism_index(rng_.mt_rng_)];
		new_creature.Mutate();

		new_population.push_back(new_creature);		
	}
	
	current_population_ = new_population;
}

//! Create a population with random creatures
void EvolutionManager::CreateRandomPopulation(int pop_size) {
	for(int i = 0; i < pop_size; ++i) {
		Creature random_creature();
		current_population_.push_back(random_creature);
	}
}