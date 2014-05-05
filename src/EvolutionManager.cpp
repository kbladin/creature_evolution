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

    //how much each fitness function should contribute to the fitness value
    float weight1, weight2, weight3, weight4, weight5, weight6;
    weight1 = SettingsManager::Instance()->GetFitnessDistanceZ();
    weight2 = SettingsManager::Instance()->GetFitnessMaxY();
    weight3 = SettingsManager::Instance()->GetFitnessAccumY();
    weight4 = SettingsManager::Instance()->GetFitnessAccumHeadY();
    weight5 = SettingsManager::Instance()->GetFitnessDeviationX();
    weight6 = SettingsManager::Instance()->GetFitnessEnergy();

    // find the max value of each fitness-value to be able to normalize
    SimData data = current_population_[0].simdata;
    float norm_dist_z = data.distance_z;
    float norm_max_y = data.max_y;
    float norm_accumulated_y = data.accumulated_y;
    float norm_deviation_x = data.deviation_x;
    float norm_accumulated_head_y = data.accumulated_head_y;
    float norm_energy = data.energy_waste;

    for(int i = 1; i < current_population_.size(); ++i) {
    	data = current_population_[i].simdata;

    	norm_dist_z = (data.distance_z > norm_dist_z) ?
    					data.distance_z : norm_dist_z;
    	norm_max_y = (data.max_y > norm_max_y) ?
    					data.max_y : norm_max_y;
    	norm_accumulated_y = (data.accumulated_y > norm_accumulated_y) ?
    					data.accumulated_y : norm_accumulated_y;
    	norm_accumulated_head_y = (data.accumulated_head_y > norm_accumulated_head_y) ?
    					data.accumulated_head_y : norm_accumulated_head_y;
    	norm_deviation_x = (data.deviation_x > norm_deviation_x) ?
    					data.deviation_x : norm_deviation_x;
    	norm_energy = (data.energy_waste > norm_energy) ?
    					data.energy_waste : norm_energy;
    }

	// calculate fitness for each creature    
    for(int i = 0; i < current_population_.size(); ++i) {
    	data = current_population_[i].simdata;
        float dist_z = data.distance_z;
        float max_y = data.max_y;
        float accumulated_y = data.accumulated_y; 
        float accumulated_head_y = data.accumulated_head_y; 
        float deviation_x = data.deviation_x; 
        float energy = data.energy_waste;

       	float fitness =
       		weight1*(dist_z/norm_dist_z) + 
       		weight2*(max_y/norm_max_y) +
       		weight3*(accumulated_y/norm_accumulated_y) +
       		weight4*(accumulated_head_y/norm_accumulated_head_y) + 
       		weight5*(deviation_x/norm_deviation_x) +
       		weight6*(energy/norm_energy);
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
    for(int i = elitism_pivot; i < current_population_.size(); i++) {
		int random_index = int_elitism_index(rng_.mt_rng_);

		Creature c = TournamentSelection();

		c.Mutate();
		
        new_population[i] = c; 
	}

	// current_population_ = new_population;
	for(int i = 0; i < current_population_.size(); ++i) {
		current_population_[i] = new_population[i];
	}
}



//! Select a creature from the population based on tournament selection.
Creature EvolutionManager::TournamentSelection() {
	int TOURNAMENT_SIZE = 3;
	Creature c; 

	std::uniform_int_distribution<int> int_dist_index_(0,
						current_population_.size()-1);

	c = current_population_[int_dist_index_(rng_.mt_rng_)];
	for (int j = 0; j < TOURNAMENT_SIZE; ++j) {
		int idx = int_dist_index_(rng_.mt_rng_);
		if(current_population_[idx].GetFitness() > 
									c.GetFitness()) {
			c = current_population_[idx];
		}
	}

	return c;
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
