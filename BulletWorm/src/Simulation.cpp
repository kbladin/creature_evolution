#include "Simulation.h"
#include "DebugDraw.h"

#include <btBulletDynamicsCommon.h>
#include <iostream>



Simulation::Simulation(void)
{
	counter = 0;

	//init world
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

	//environment
	dynamicsWorld->setGravity(btVector3(0,-10,0));
	groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	//creature
	worm = new WormBulletCreature(60,dynamicsWorld,btVector3(0.0,0.0,0.0));

}


Simulation::~Simulation(void)
{
	delete worm;

	dynamicsWorld->removeRigidBody(fallRigidBody);
	delete fallRigidBody->getMotionState();
	delete fallRigidBody;

	dynamicsWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;


	delete fallShape;

	delete groundShape;


	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}

void Simulation::step()
{
	dynamicsWorld->stepSimulation(1/600.f,1000);
	worm->updateMovement((float)counter/600.0);
	counter++;
}

btDiscreteDynamicsWorld* Simulation::getDynamicsWorld()
{
	return dynamicsWorld;
}