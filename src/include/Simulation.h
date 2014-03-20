#ifndef SIMULATION_H
#define SIMULATION_H

// C++
#include <iostream>
#include <vector>
#include <algorithm>
// External
#include <btBulletDynamicsCommon.h>
// Internal
#include "WormBulletCreature.h"

class Simulation
{
public:
	Simulation();
	~Simulation(void);
	void AddCreatureToWorld(WormBulletCreature* worm);
	void RemoveCreatureFromWorld(WormBulletCreature* worm);
	void Step(float dt);
	btDiscreteDynamicsWorld* GetDynamicsWorld();

private:
	std::vector<WormBulletCreature*> creatures_;

	btBroadphaseInterface* broad_phase_;
	btDefaultCollisionConfiguration* collision_configuration_;
	btCollisionDispatcher* dispatcher_;
	btSequentialImpulseConstraintSolver* solver_;
	btDiscreteDynamicsWorld* dynamics_world_;

	btCollisionShape* ground_shape_;

	btDefaultMotionState* ground_motion_state_;
	btRigidBody* ground_rigid_body_;


	btDefaultMotionState* fall_motion_state_;
	btScalar mass_;

	float counter_;
};


#endif // SIMULATION_H
