#ifndef SIMULATION_H
#define SIMULATION_H

#include <btBulletDynamicsCommon.h>

#include "WormBulletCreature.h"

class Simulation
{
public:
	Simulation(std::vector<float> genes);
	~Simulation(void);
	void step();
	void debugDraw();
	btDiscreteDynamicsWorld* getDynamicsWorld();
	float getFitnessValue();

private:
	WormBulletCreature* worm;

	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	btCollisionShape* groundShape;

	btDefaultMotionState* groundMotionState;
	btRigidBody* groundRigidBody;


	btDefaultMotionState* fallMotionState;
	btScalar mass;


	int counter;
};


#endif // SIMULATION_H
