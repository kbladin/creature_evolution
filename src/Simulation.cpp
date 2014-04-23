#include "Simulation.h"
#include <iostream>

Simulation::Simulation() {
  counter_ = 0;
  fps_ = 60;
  broad_phase_ = new btDbvtBroadphase();
  collision_configuration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collision_configuration_);
  solver_ = new btSequentialImpulseConstraintSolver;

  dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_,
    broad_phase_, solver_, collision_configuration_);
}

Simulation::~Simulation() {
  std::cout << "DESTROY DA BASE SIMULATION!!!" << std::endl;

  delete dynamics_world_;
  delete solver_;
  delete collision_configuration_;
  delete dispatcher_;
  delete broad_phase_;
}

void Simulation::SetFps(int fps) {
  fps_ = fps;
}

int Simulation::GetFps() {
  return fps_;
}

btDiscreteDynamicsWorld* Simulation::GetDynamicsWorld() {
  return dynamics_world_;
}

float Simulation::GetCounterTime() {
  return counter_;
}

void Simulation::ResetTime() {
  counter_ = 0.0f;
}