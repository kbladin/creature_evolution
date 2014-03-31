#include "Creature.h"
#include <ctime>

AutoInitRNG Creature::rng_;

//! Constructor that creates a Creature based on the chromosome input.
/*! Calculates the fitness value that the creature has.
	\param chromosome The creature that will be created. 
*/
Creature::Creature(Chromosome chromosome) : 
	chromosome_(chromosome) ,
	fitness_(CalculateFitness(chromosome_)){}

//! A constructor that creates a random creature. 
Creature::Creature() : 
	chromosome_(Chromosome()) ,
	fitness_(CalculateFitness(chromosome_)) {}

//! Return the chromosome
Chromosome Creature::GetChromosome() const{
	return chromosome_;
}

//! Return the fitnessvalue for the creature
float Creature::GetFitness() const{
	return fitness_;
}

//! A function to get children. 
/*!
	Get one creature and try to mate with the current creature.
	If they will not mate due to the crossover rate, the parents itself
	will returned as the children.
	\param mate The other creature to mate with
	\param crossover How the odds are if they should mate or not.
	\return children The two new children from the two parents.
*/
std::vector<Chromosome> Creature::Crossover(Creature mate, float crossover){

	// generate a random number between 0 and 1
	std::uniform_real_distribution<float> crossover_decider(0,1);

	std::vector<Chromosome> children;
	
	// depends on the crossover rate, should we mate or not
	if (crossover_decider(rng_.mt_rng_) <= crossover) {
		children = chromosome_.CrossOverMate(mate.GetChromosome());
		return children;
	}

	children.push_back(chromosome_);
	children.push_back(mate.GetChromosome());

	// should return the parents if not mated
	return children; 
}

//! The fitness function that will deside how good our creature are. 
float Creature::CalculateFitness(Chromosome chromosome){
	std::clock_t start_time;
	start_time = std::clock();

	WormBulletCreature* worm = new WormBulletCreature(chromosome.GetGene(), btVector3(0.0, 1.0, 0.0));
	Simulation sim;
	sim.AddCreatureToWorld(worm);

	int fps = 30;
	int n_seconds = 60;
	for (int i = 0; i < fps*n_seconds; ++i){
		sim.Step(1/float(fps));

	}
	float fitness = worm->GetCenterOfMass().getZ();

	sim.RemoveCreatureFromWorld(worm);
	delete worm;

	//std::cout << "Simulation time: " << float (std::clock() - start_time) / CLOCKS_PER_SEC  << " s" << std::endl;

	return fitness;
}