#include "VizSimulation.h"

VizSimulation::VizSimulation() {
  // self collision
  bt_creature_collidies_with_ =
    collisiontypes::COL_GROUND;// | collisiontypes::COL_CREATURE;

  ground_collidies_with_ = collisiontypes::COL_CREATURE;

  SetupEnvironment();
}

VizSimulation::~VizSimulation() {

  dynamics_world_->removeRigidBody(ground_rigid_body_);
  delete ground_rigid_body_->getMotionState();
  delete ground_rigid_body_;
  delete ground_shape_;
}

void VizSimulation::SetupEnvironment() {
  dynamics_world_->setGravity(btVector3(0, -10, 0));
  ground_shape_ = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

  ground_motion_state_ =
    new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
    btVector3(0, -1, 0)));

  btRigidBody::btRigidBodyConstructionInfo ground_rigid_bodyCI(0,
    ground_motion_state_, ground_shape_, btVector3(0, 0, 0));

  ground_rigid_body_ = new btRigidBody(ground_rigid_bodyCI);
  ground_rigid_body_->setFriction(1.0f);

  dynamics_world_->addRigidBody(ground_rigid_body_,
    collisiontypes::COL_GROUND, ground_collidies_with_);
}

void VizSimulation::Step(float dt) {
  dynamics_world_->stepSimulation(dt, 1);
  counter_ += dt;
}

float VizSimulation::GetCounter() {
  return counter_;
}

int VizSimulation::GetCollisionType(){
  return bt_creature_collidies_with_;
}

void VizSimulation::ClearForces() {
  dynamics_world_->clearForces();
}