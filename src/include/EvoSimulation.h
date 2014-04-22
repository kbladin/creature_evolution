#ifndef EVOSIMULATION_H
#define EVOSIMULATION_H

#include <vector>
#include "Simulation.h"
#include "Creature.h"
#include "BulletCreature.h"

typedef std::vector<Creature> Population;

class EvoSimulation : public Simulation {
  public:
    EvoSimulation();
    ~EvoSimulation();

    virtual void Step(float dt);
    virtual void SetupEnvironment();

    void AddPopulation(Population population);
    Population SimulatePopulation();

  private:
    btCollisionShape* ground_shape_;
    btDefaultMotionState* ground_motion_state_;
    btRigidBody* ground_rigid_body_;

    std::vector<BulletCreature> bt_population_;

    int bt_creature_collidies_with_;
    int ground_collidies_with_;

    int time_to_simulate_;
};

#endif  // EVOSIMULATION_H
