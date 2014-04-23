#ifndef VIZSIMULATION_H
#define VIZSIMULATION_H

#include "Simulation.h"

class VizSimulation : public Simulation {
  public:
    VizSimulation();
    ~VizSimulation();

    virtual void Step(float dt);
    virtual void SetupEnvironment();
    void ClearForces();

    float GetCounter();
    int GetCollisionType();
  private:
    btCollisionShape* ground_shape_;
    btDefaultMotionState* ground_motion_state_;
    btRigidBody* ground_rigid_body_;

    int bt_creature_collidies_with_;
    int ground_collidies_with_;
};

#endif	// VIZSIMULATION_H