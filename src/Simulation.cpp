#include "SimulationV2.h"

SimulationV2::SimulationV2() {
  counter_ = 0;
  fps_ = 60;
  broad_phase_ = new btDbvtBroadphase();
  collision_configuration_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collision_configuration_);
  solver_ = new btSequentialImpulseConstraintSolver;

  dynamics_world_ = new btDiscreteDynamicsWorld(dispatcher_,
    broad_phase_, solver_, collision_configuration_);
}

SimulationV2::~SimulationV2() {
  delete dynamics_world_;
  delete solver_;
  delete collision_configuration_;
  delete dispatcher_;
  delete broad_phase_;
}

void SimulationV2::SetFps(int fps) {
  fps_ = fps;
}

int SimulationV2::GetFps() {
  return fps_;
}

btDiscreteDynamicsWorld* SimulationV2::GetDynamicsWorld() {
  return dynamics_world_;
}
