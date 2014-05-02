#include "EvolutionManager.h"
#include "SettingsManager.h"
#include "Simulation.h"
#include <chrono>
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
    std::clock_t start_time;
	start_time = std::clock();

	int max_gen = SettingsManager::Instance()->GetMaxGenerations();
	int pop_size = SettingsManager::Instance()->GetPopulationSize();
  Creature best;

	// Creates a new random population
	current_population_ = CreateRandomPopulation(pop_size);
	std::chrono::time_point<std::chrono::system_clock> start, end;
    for (int i = 0; i < max_gen; ++i){
		std::cout << "Generation: " << i << std::endl <<
        "Simulating..." << std::endl;
        SimulatePopulation();

        CalculateFitnessOnPopulation();
        SortPopulation();

		// save the population and the best creatures
        // SettingsManager::Instance()->AddBestCreature(GetBestCreature());
        //best = GetBestCreature();
        //TODO: send Creature via signal
        emit NewCreature(GetBestCreature());
        //best_creatures_.push_back(best);
        NextGeneration();
	}
	std::cout << "Total simulation time: " << float(std::clock() - start_time) / CLOCKS_PER_SEC  << " s" << std::endl;
}

//! Prints the fitness value for the best creature in all different generations.
void EvolutionManager::PrintBestFitnessValues(){
	for(int i=0; i<best_creatures_.size(); i++){
		std::cout << "🐛" << "Generation " << i+1 << ". Best fitness: " 
		<< best_creatures_[i].GetFitness() << std::endl;
	}

}

void EvolutionManager::PrintPopulation() {
	for(int i = 0; i < current_population_.size(); ++i) {
		std::cout << "Creature " << i << " " << current_population_[i].GetFitness() << std::endl;
	}
}

//! Returns the best creature as of when this method is called
Creature EvolutionManager::GetBestCreature() {
    return current_population_[0];
}

Creature EvolutionManager::GetBestCreatureFromLastGeneration() {
	return best_creatures_.back();
}

Population EvolutionManager::GetAllBestCreatures() {
	return best_creatures_;
}

//! Simulates all creatures in population
void EvolutionManager::SimulatePopulation() {
    Simulation sim_world;
    
    sim_world.AddPopulation(current_population_, false);
    current_population_ = sim_world.SimulatePopulation();
}

//! Calculates fitness values for all creatures in population by 
// looking at values stored during simulation
void EvolutionManager::CalculateFitnessOnPopulation() {

    /*  TO DO: här ändra om hur fitnessvärden ska räknas ut.
        Vikta ihop olika sorter. gå längst, vara högst över marken osv.
        Komma ihåg att normalisera värdena när de viktas ihop!
    */

    SimData data = current_population_[0].GetSimData();
    float norm_dist_z =data.distance_forward;
    float norm_max_height=data.max_height;

    std::vector<float> weights; 

    weights.push_back(1.0f);
    weights.push_back(0.5f);

    for(int i = 1; i < current_population_.size(); ++i) {
    	SimData data = current_population_[i].GetSimData();

    	if(data.distance_forward > norm_dist_z)
    		norm_dist_z = data.distance_forward;

    	if(data.max_height > norm_max_height)
    		norm_max_height = data.max_height;

    }
    
    for(int i = 0; i < current_population_.size(); ++i) {
    	SimData data = current_population_[i].GetSimData();
        float dist_z = data.distance_forward;
        float max_height = data.max_height; 

       	float fitness = weights[0]*(dist_z/norm_dist_z) + weights[1]*(max_height/norm_max_height);

        current_population_[i].SetFitness(fitness);
    }
}

//! Sorts the current population based on fitness value. Should only be called once fitness
// values have been obtained
void EvolutionManager::SortPopulation() {
	std::sort(current_population_.begin(), current_population_.end(), CreatureLargerThan());
}


//! Evolves the current population based on simple mutation and elitism
void EvolutionManager::NextGeneration() {
	float elitism = SettingsManager::Instance()->GetElitism();
	float mutation = SettingsManager::Instance()->GetMutation();

	int elitism_pivot = static_cast<int>(current_population_.size() * elitism);

	Population new_population (&current_population_[0],
		 &current_population_[elitism_pivot]);

	new_population.resize(current_population_.size());

	std::uniform_int_distribution<int> int_elitism_index(0, elitism_pivot);

	//Creature new_creature;
    for(int i = elitism_pivot; i < current_population_.size() - 1; i++) {
		int random_index = int_elitism_index(rng_.mt_rng_);

		std::vector<Creature> parents = TournamentSelection();
		//parents.push_back(current_population_[random_index]);
		//parents.push_back(current_population_[random_index]);
		std::vector<Creature> new_creatures = parents[0].Crossover(parents[1]);

		new_creatures[0].Mutate();
		new_creatures[1].Mutate();

        new_population[i] = new_creatures[0];

        // ser till att om pop. size är udda så läggs inte denna till. dock kanske borde skrivas på annat sätt.
        if(i != current_population_.size() - 1)
	        new_population[i+1] = new_creatures[1];
	}

	// current_population_ = new_population;
	for(int i = 0; i < current_population_.size(); ++i) {
		current_population_[i] = new_population[i];
	}
}

//! Select parents for crossover and mutation
std::vector<Creature> EvolutionManager::TournamentSelection() {
	int TOURNAMENT_SIZE = 3;
	std::vector<Creature> parents;
	parents.resize(2);
	std::uniform_int_distribution<int> int_dist_index_(0,
						current_population_.size()-1);

	for (int i = 0; i < 2; ++i) {
		parents[i] = current_population_[int_dist_index_(rng_.mt_rng_)];
		for (int j = 0; j < TOURNAMENT_SIZE; ++j) {
			int idx = int_dist_index_(rng_.mt_rng_);
			if(current_population_[idx].GetFitness() > 
										parents[i].GetFitness()) {
				parents[i] = current_population_[idx];
			}
		}
	}

	return parents;
}

//! Create a population with random creatures
Population EvolutionManager::CreateRandomPopulation(int pop_size) {
	Population random_pop;
	for(int i = 0; i < pop_size; ++i) {
		Creature random_creature;
		random_pop.push_back(random_creature);
	}
	return random_pop;
}

// void EvolutionManager::GenerationDone(Creature new_creature) {
//   emit NewCreature(new_creature);
// }
