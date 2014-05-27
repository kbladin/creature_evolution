#ifndef Simulation_H
#define Simulation_H

#include <vector>
#include "Creature.h"
#include "BulletCreature.h"
#include "Node.h"

#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0,
    COL_CREATURE = BIT(0),
    COL_GROUND = BIT(1)
};

typedef std::vector<Creature> Population;

class Simulation {
  public:
    Simulation();
    ~Simulation();

    virtual void Step(float dt);
    virtual void SetupEnvironment();

    void AddPopulation(Population population, bool disp);
    Population SimulatePopulation();
    std::vector<Node> GetNodes();
    btVector3 GetLastCreatureCoords();
  private:
    btBroadphaseInterface* broad_phase_;
    btDefaultCollisionConfiguration* collision_configuration_;
    btCollisionDispatcher* dispatcher_;
    btSequentialImpulseConstraintSolver* solver_;
    btDiscreteDynamicsWorld* dynamics_world_;


    std::vector<BulletCreature*> bt_population_;

    btCollisionShape* ground_shape_;
    btDefaultMotionState* ground_motion_state_;
    btRigidBody* ground_rigid_body_;
    Material ground_material_;

    btCollisionShape* light_shape_;
    btRigidBody* light_rigid_body_;
    Material light_material_;


    int bt_creature_collidies_with_;
    int ground_collidies_with_;

    int time_to_simulate_;
    int fps_;
    float counter_;
};

#endif  // Simulation_H
