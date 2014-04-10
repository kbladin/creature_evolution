#include "Simulation.h"


//! Setup a default physics world with an infinite ground plane.
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

//! Destructor. Delete all dynamic allocated things for Bullet.
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
    RemoveCreature();
}

//! Adds a creature from the Evolution process to the physical world.
void Simulation::AddCreature(Creature& creature){
    creature_ = &creature;
    bullet_creature_ = new BulletCreature(creature_);
}

/*! Removes the creature's rigid bodies and joints.
 Can only be called if a creature has been added.*/
void Simulation::RemoveCreature() {
        delete bullet_creature_;
        bullet_creature_ = NULL;
}

//! Update the 'motors' on the creature and step the physical world.
void Simulation::Step(float dt)
{
    std::vector<float> input(1,counter_);
    bullet_creature_->UpdateMotors(input);
    dynamics_world_->stepSimulation(dt,1000);
    counter_ += dt;
	dynamics_world_->stepSimulation(dt,1000);
	counter_ += dt;
	
}

//! Returns the current btDiscreteDynamicsWorld pointer
btDiscreteDynamicsWorld* Simulation::GetDynamicsWorld()
{
	return dynamics_world_;
}

//! Starts the simulation process with a predetermined fps and time.
void Simulation::Simulate() {
    int fps = 30;
    int n_seconds = 60;
    for (int i = 0; i < fps*n_seconds; ++i){
        Step(1/float(fps));

	}
}

std::vector<btRigidBody*> Simulation::GetRigidBodies() {
    std::vector<btRigidBody*> placeholder;
    btRigidBody* dummy_body = new btRigidBody(1.0f,NULL, NULL,btVector3(0, 0, 0));
    placeholder.push_back(dummy_body);
    return placeholder;
}
