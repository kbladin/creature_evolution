#include "Creature.h"

//! Default constructor creates a random creature.
Creature::Creature() {

}

//! Destructor. Deletes all rigid bodies etc
Creature::~Creature() {

}

//! Set given fitness value on creature
void Creature::SetFitness(float fitness) {
	fitness_ = fitness;
}

//! Return the fitnessvalue for the creature
float Creature::GetFitness() const {
    return fitness_;
}

//! The fitness function that will decide how good our creature are.
void Creature::CalculateFitness(){

}

/*! Simple mutation algorithm on creature.
 This should be extended to try more cases. */
void Creature::Mutate() {

}

//! PLACEHOLDER
float Creature::GetPos() {
	return 0.0f;
}

//! PLACEHOLDER
float Creature::GetSpeed() {
	return 0.0f;
}

//! PLACEHOLDER
void Creature::UpdateMovement(float time) {

}

//! PLACEHOLDER
std::vector<btRigidBody*> Creature::GetRigidBodies() {
	std::vector<btRigidBody*> placeholder;
	btRigidBody* dummy_body = new btRigidBody(1.0f,NULL, NULL,btVector3(0, 0, 0));
	placeholder.push_back(dummy_body);
	return placeholder;
}

//! PLACEHOLDER
std::vector<btHingeConstraint*> Creature::GetJoints() {
	std::vector<btHingeConstraint*> placeholder;
	return placeholder;
}

