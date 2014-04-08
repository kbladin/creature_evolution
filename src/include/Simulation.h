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

//forward declaration
class Creature;

/*! Handles the simulation of the Bullet physics world.
	This is used both for the evolution process and the rendering process.
 */
class Simulation
{
public:
	Simulation();
	~Simulation(void);
	void AddCreature(Creature creature);
	void RemoveCreature();
	void Step(float dt);
	void Simulate();
	btDiscreteDynamicsWorld* GetDynamicsWorld();

private:
	Creature* creature_;

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
