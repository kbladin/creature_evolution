#include "Creature.h"

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

/*! Simple mutation algorithm on creature.
 This should be extended to try more cases. */
void Creature::Mutate() {

}

SimData Creature::GetSimData() {
    return simdata_;
}

void Creature::SetSimdata(SimData d) {
    simdata_ = d;
}
