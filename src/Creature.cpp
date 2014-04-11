#include "Creature.h"

AutoInitRNG Creature::rng_;

//! Default constructor creates a random creature.
Creature::Creature() {
	fitness_ = -1.0f;
}

//! Destructor. Deletes all rigid bodies etc
Creature::~Creature() {

}

std::vector<float> Creature::CalculateBrainOutput(std::vector<float> input) {
    return brain_.CalculateOutput(input);
}

//! Set given fitness value on creature
void Creature::SetFitness(float fitness) {
	fitness_ = fitness;
}

//! Return the fitnessvalue for the creature
float Creature::GetFitness() const {
    return fitness_;
}

Brain Creature::GetBrain(){
	return brain_;
}

/*! Simple mutation algorithm on creature.
 This should be extended to try more cases. */
void Creature::Mutate() {
	//TODO: if the mutation should be done or not depending on the ratio
	std::uniform_real_distribution<float> int_dist(0.0f,1.0f);
	double should_mutate = int_dist(rng_.mt_rng_);
	if( SettingsManager::Instance()->GetMutation() >= should_mutate) {
		brain_.Mutate();
	}
}

SimData Creature::GetSimData() {
    return simdata_;
}

void Creature::SetSimData(SimData d) {
    simdata_ = d;
}

std::vector<Creature> Creature::Crossover(Creature mate){
	std::vector<Creature> children;
	std::vector<Brain> childrens_brain;
	children.resize(2);
	childrens_brain.resize(2);

	std::uniform_real_distribution<float> int_dist(0.0f,1.0f);

	double should_crossover = int_dist(rng_.mt_rng_);
	SettingsManager::Instance()->GetCrossover();

	if(SettingsManager::Instance()->GetCrossover() >= should_crossover) {
	// TODO: if crossover should be done, else return the incomming creatures
		childrens_brain = brain_.Crossover(mate.GetBrain());
		children[0].brain_ = childrens_brain[0];
		children[1].brain_ = childrens_brain[1];
	}
	else {
		children[0].brain_ = brain_;
		children[1].brain_ = mate.GetBrain();
	}

	return children;

}
