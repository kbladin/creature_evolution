#ifndef SIMULATIONV2_H
#define SIMULATIONV2_H

#include <btBulletDynamicsCommon.h>

#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0,
    COL_CREATURE = BIT(0),
    COL_GROUND = BIT(1)
};

class SimulationV2 {
  public:
    SimulationV2();
    virtual ~SimulationV2();

    virtual void Step(float dt) = 0;
    virtual void SetupEnvironment() = 0;

    btDiscreteDynamicsWorld* GetDynamicsWorld();
    void SetFps(int fps);
    int GetFps();
  protected:
    btBroadphaseInterface* broad_phase_;
    btDefaultCollisionConfiguration* collision_configuration_;
    btCollisionDispatcher* dispatcher_;
    btSequentialImpulseConstraintSolver* solver_;
    btDiscreteDynamicsWorld* dynamics_world_;

    float counter_;
    int fps_;
};

#endif	// SIMULATIONV2_H