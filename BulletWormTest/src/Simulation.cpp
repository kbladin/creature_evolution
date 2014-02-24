#include "Simulation.h"
#include "DebugDraw.h"

#include <btBulletDynamicsCommon.h>
#include <iostream>



Simulation::Simulation(void)
{
	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-10,0));


	groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);

	fallShape = new btSphereShape(0.1);


	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);


	fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,2,0)));
	mass = 1;
	btVector3 fallInertia(0,0,0);
	fallShape->calculateLocalInertia(mass,fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,fallMotionState,fallShape,fallInertia);
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);
}


Simulation::~Simulation(void)
{
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
	dynamicsWorld->stepSimulation(1/6000.f,1000);

	btTransform trans;
	fallRigidBody->getMotionState()->getWorldTransform(trans);

	std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
}

btDiscreteDynamicsWorld* Simulation::getDynamicsWorld()
{
	return dynamicsWorld;
}