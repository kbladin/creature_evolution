#include "Simulation.h"

Simulation::Simulation()
{
	counter_ = 0;

	//init world
	broad_phase_ = new btDbvtBroadphase();
	collision_configuration_ = new btDefaultCollisionConfiguration();
	dispatcher_ = new btCollisionDispatcher(collision_configuration_);
	solver_ = new btSequentialImpulseConstraintSolver;
	dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_,broad_phase_,solver_,collision_configuration_);

	//environment
	dynamics_world_->setGravity(btVector3(0,-10,0));
	ground_shape_ = new btStaticPlaneShape(btVector3(0,1,0),1);
	ground_motion_state_ = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo ground_rigid_bodyCI(0,ground_motion_state_,ground_shape_,btVector3(0,0,0));
	ground_rigid_body_ = new btRigidBody(ground_rigid_bodyCI);
	ground_rigid_body_->setFriction(1.0f);
	dynamics_world_->addRigidBody(ground_rigid_body_);
}

Simulation::~Simulation(void)
{
	dynamics_world_->removeRigidBody(ground_rigid_body_);
	delete ground_rigid_body_->getMotionState();
	delete ground_rigid_body_;

	delete ground_shape_;


	delete dynamics_world_;
	delete solver_;
	delete collision_configuration_;
	delete dispatcher_;
	delete broad_phase_;	
}

void Simulation::AddCreature(Creature creature){

	creature_ = &creature;

	std::vector<btRigidBody*> rigid_bodies = creature.GetRigidBodies();
	std::vector<btHingeConstraint*> joints = creature.GetJoints();
	
	//Add bodies
	for(int i=0; i < rigid_bodies.size(); i++){
		dynamics_world_->addRigidBody(rigid_bodies[i]);

	}
	//Add joints
	for(int i=0; i < joints.size(); i++){
		dynamics_world_->addConstraint(joints[i], true);
	}
}

void Simulation::RemoveCreature() {
	std::vector<btRigidBody*> rigid_bodies = creature_.GetRigidBodies();
	std::vector<btHingeConstraint*> joints = creature_.GetJoints();

	//Add bodies
	for(int i=0; i < rigid_bodies.size(); i++){
		dynamics_world_->removeRigidBody(rigid_bodies[i]);

	}
	//Add joints
	for(int i=0; i < joints.size(); i++){
		dynamics_world_->removeConstraint(joints[i], true);
	}
	

}

void Simulation::Step(float dt)
{

	creatures_.UpdateMovement(counter_);
	dynamics_world_->stepSimulation(dt,1000);
	counter_ += dt;
	
}

btDiscreteDynamicsWorld* Simulation::GetDynamicsWorld()
{
	return dynamics_world_;
}

void Simulation::Simulate() {
	int fps = 30;
	int n_seconds = 60;
	for (int i = 0; i < fps*n_seconds; ++i){
		Step(1/float(fps));
	}
}