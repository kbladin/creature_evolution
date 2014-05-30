#include "EvolutionManager.h"
#include "SettingsManager.h"
#include "Simulation.h"
#include <chrono>

#include <QMutexLocker>
AutoInitRNG EvolutionManager::rng_;

//! Constructor
/*! 
*/
EvolutionManager::EvolutionManager(){
    end_now_request_ = false;
    mutex_ = new QBasicMutex();
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
    CreateNewRandomPopulation();
    RunEvolution();
}

//! Creates a new random population
void EvolutionManager::CreateNewRandomPopulation(){
    current_population_.clear();

    // Creates a new random population
    int pop_size = SettingsManager::Instance()->GetPopulationSize();
    current_population_ = CreateRandomPopulation(pop_size);
}

void EvolutionManager::RunEvolution(){
    end_now_request_ = false;
    std::clock_t start_time;
    start_time = std::clock();

    int max_gen = SettingsManager::Instance()->GetMaxGenerations();

    int i = 0;
    while(i < max_gen) {
        if(!NeedEndNow()) {
            std::cout << "Generation: " << i << std::endl <<
            "Simulating..." << std::endl;
            NextGeneration();
            SimulatePopulation();
            CalculateFitnessOnPopulation();
            SortPopulation();
            PrintBestFitnessValues();
            
            emit NewCreature(GetBestCreature());
            
            NextGeneration();
            i++;
        }
        else
            break;
    }

    std::cout << "Total simulation time: " << float(std::clock() - start_time) / CLOCKS_PER_SEC  << " s" << std::endl;
}

//! Prints the fitness value for the best creature in all different generations.
void EvolutionManager::PrintBestFitnessValues(){
    std::cout <<
    "Distance to light = " << current_population_[0].simdata.distance_light << std::endl <<
    "Distance z = " << current_population_[0].simdata.distance_z << std::endl <<
    "Max y = " << current_population_[0].simdata.max_y << std::endl <<
    "Accumulated y = " << current_population_[0].simdata.accumulated_y << std::endl <<
    "Accumulated head y = " << current_population_[0].simdata.accumulated_head_y << std::endl <<
    "Deviation x = " << current_population_[0].simdata.deviation_x << std::endl <<
    "Energy waste = " << current_population_[0].simdata.energy_waste << std::endl;
}

void EvolutionManager::PrintPopulation() {
	for(int i = 0; i < current_population_.size(); ++i) {
		std::cout << "Creature " << i << " " << current_population_[i].simdata.distance_light << std::endl;
	}
}

//! Returns the best creature as of when this method is called
Creature EvolutionManager::GetBestCreature() {
    return current_population_[0];
}

//! Returns the best creature from the last generation
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
    float weight1, weight2, weight3, weight4, weight5, weight6, weight7;
    weight1 = SettingsManager::Instance()->GetFitnessDistanceLight();
    weight2 = SettingsManager::Instance()->GetFitnessDistanceZ();
    weight3 = SettingsManager::Instance()->GetFitnessMaxY();
    weight4 = SettingsManager::Instance()->GetFitnessAccumY();
    weight5 = SettingsManager::Instance()->GetFitnessAccumHeadY();
    weight6 = SettingsManager::Instance()->GetFitnessDeviationX();
    weight7 = SettingsManager::Instance()->GetFitnessEnergy();

    // find the max value of each fitness-value to be able to normalize
    SimData data = current_population_[0].simdata;
    float norm_dist_light = data.distance_light;
    float norm_dist_z = data.distance_z;
    float norm_max_y = data.max_y;
    float norm_accumulated_y = data.accumulated_y;
    float norm_deviation_x = data.deviation_x;
    float norm_accumulated_head_y = data.accumulated_head_y;
    float norm_energy = data.energy_waste;

    for(int i = 1; i < current_population_.size(); ++i) {
    	data = current_population_[i].simdata;

        norm_dist_light = (data.distance_light > norm_dist_light) ?
                        data.distance_light : norm_dist_light;
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
        float dist_light = data.distance_light;
        float dist_z = data.distance_z;
        float max_y = data.max_y;
        float accumulated_y = data.accumulated_y; 
        float accumulated_head_y = data.accumulated_head_y; 
        float deviation_x = data.deviation_x; 
        float energy = data.energy_waste;

       	float fitness =
            weight1*(dist_light/norm_dist_light) +
            weight2*(dist_z/norm_dist_z) +
            weight3*(max_y/norm_max_y) +
            weight4*(accumulated_y/norm_accumulated_y) +
            weight5*(accumulated_head_y/norm_accumulated_head_y) +
            weight6*(deviation_x/norm_deviation_x) +
            weight7*(energy/norm_energy);
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

	current_population_ = new_population;
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


void EvolutionManager::RequestEndNow() {
    std::cout << "End Sim in thread!" << std::endl;
    QMutexLocker locker(mutex_);
    end_now_request_ = true;
}

bool EvolutionManager::NeedEndNow() {
    QMutexLocker locker(mutex_);
    return end_now_request_;
}

void EvolutionManager::RequestEndNowFunc() {
    QMutexLocker locker(mutex_);
    end_now_request_ = true;
}

void EvolutionManager::RequestStart() {
    QMutexLocker locker(mutex_);
    end_now_request_ = false;
}
