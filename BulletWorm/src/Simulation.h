#ifndef SIMULATION_H
#define SIMULATION_H

#include <btBulletDynamicsCommon.h>

#include "WormBulletCreature.h"


class Simulation
{
public:
	Simulation(void);
	~Simulation(void);
	void step();
	void debugDraw();
	btDiscreteDynamicsWorld* getDynamicsWorld();

private:
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	btCollisionShape* groundShape;

	btCollisionShape* fallShape;


	btDefaultMotionState* groundMotionState;
	btRigidBody* groundRigidBody;


	btDefaultMotionState* fallMotionState;
	btScalar mass;
	btRigidBody* fallRigidBody;

	WormBulletCreature* worm;
};


#endif // SIMULATION_H
