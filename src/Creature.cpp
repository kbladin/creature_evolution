#include "Creature.h"

//! Default constructor creates a random creature.
Creature::Creature() {
	fitness_ = -1.0f;
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
    std::vector<float> input;
    input.push_back(time);
    std::vector<float> signal = brain.CalculateOutput(input);
    for(int i=0; i < m_joints_.size(); i++) {
        m_joints_[i]->enableAngularMotor(true, 20.0*signal[i], 10.0);
    }
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

void Creature::ResetBodies() {
	//reset all rigid bodies to zero
}
