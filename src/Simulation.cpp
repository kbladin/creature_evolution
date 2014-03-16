#include "Simulation.h"
#include "DebugDraw.h"

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <vector>


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

void Simulation::AddCreatureToWorld(WormBulletCreature* worm){
	creatures_.push_back(worm);
	worm->AddToDynamicsWorld(GetDynamicsWorld());
}

void Simulation::RemoveCreatureFromWorld(WormBulletCreature* worm){
	for( std::vector<WormBulletCreature*>::iterator iter = creatures_.begin(); iter != creatures_.end(); ++iter ) {
	    if( *iter == worm ){
			creatures_[iter - creatures_.begin()]->RemoveFromDynamicsWorld(GetDynamicsWorld());
	        creatures_.erase(iter);
	        return;
	    }
	}
	std::cout << "Warning! Could not remove creature from the list of creatures!" << std::endl;
}

void Simulation::Step(float dt)
{
	for (int i = 0; i < creatures_.size(); ++i){
		creatures_[i]->UpdateMovement(counter_);
	}
	dynamics_world_->stepSimulation(dt,1000);
	counter_ += dt;
}

btDiscreteDynamicsWorld* Simulation::GetDynamicsWorld()
{
	return dynamics_world_;
}
