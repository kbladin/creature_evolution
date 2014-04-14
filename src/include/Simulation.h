#ifndef SIMULATION_H
#define SIMULATION_H

// C++
#include <iostream>
#include <vector>
#include <algorithm>
// External
#include <btBulletDynamicsCommon.h>
// Internal
#include "Creature.h"
#include "BulletCreature.h"

//forward declaration
//class Creature;

#define BIT(x) (1<<(x))
enum collisiontypes {
    COL_NOTHING = 0, //<Collide with nothing
    COL_CREATURE = BIT(0),
    COL_GROUND = BIT(1) //<Collide with ships
    //COL_ENVIRONMENT = BIT(1)
};



//! Handles the simulation of the Bullet physics world.
/*	This is used both for the evolution process and the rendering process.*/
class Simulation
{

public:
	Simulation();
	~Simulation(void);
    void AddCreature(Creature creature);
    void AddPopulation(std::vector<Creature> population);
	void RemoveCreature();
	void Step(float dt);
	void StepPopulation(float dt);

	Creature Simulate();
	std::vector<Creature> SimulatePopulation();

	btDiscreteDynamicsWorld* GetDynamicsWorld();
    std::vector<btRigidBody*> GetRigidBodies();
	BulletCreature* GetCurrentBulletCreature();

private:
    Creature creature_;
    BulletCreature* bullet_creature_;
    
    std::vector<Creature> population_;
    std::vector<BulletCreature*> bt_population_;

	btBroadphaseInterface* broad_phase_;
	btDefaultCollisionConfiguration* collision_configuration_;
	btCollisionDispatcher* dispatcher_;
	btSequentialImpulseConstraintSolver* solver_;
	btDiscreteDynamicsWorld* dynamics_world_;

	btCollisionShape* ground_shape_;

	btDefaultMotionState* ground_motion_state_;
	btRigidBody* ground_rigid_body_;


	int bt_creature_collidies_with;
	int ground_collidies_with;


	btScalar mass_;

	float counter_;
};

#endif // SIMULATION_H
