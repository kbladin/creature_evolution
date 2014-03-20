#include "WormBulletCreature.h"
#include <memory>
#include <Node.h>
WormBulletCreature::WormBulletCreature(const std::vector<float> genes, const btVector3& position) {
	genes_ = genes;
	int segment_count = genes_.size()/4;

	m_bodies_.resize(segment_count+1);
	m_joints_.resize(segment_count);
	

	//world position
	btTransform offset;
	offset.setIdentity();
	offset.setOrigin(position);

	//setup segments
	btScalar shape_radius = 0.1;
	//m_shape_ = new btSphereShape(shape_radius);
	m_shape_ = new btBoxShape(btVector3(shape_radius*2,shape_radius,shape_radius*2));
	mass_ = 5;
	btVector3 fallInertia(0,0,0);
	m_shape_->calculateLocalInertia(mass_,fallInertia);

	btDefaultMotionState* motion_state;
	btTransform transform;
	for(int i=0; i < m_bodies_.size(); i++) {
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(0.0), btScalar(i*shape_radius*2)));

		motion_state = new btDefaultMotionState(offset*transform);
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass_,motion_state,m_shape_,fallInertia);
		m_bodies_[i] = new btRigidBody(fallRigidBodyCI);
		m_bodies_[i]->setFriction(0.1f);

		//damping
		//m_bodies_[i]->setDamping(0.05f, 0.85f);
		//m_bodies_[i]->setDeactivationTime(0.8f);
		//m_bodies_[i]->setSleepingThresholds(1.6f, 2.5f);
	}
	
	//setup joints
	btTransform localA, localB;
	for(int i=0; i < m_joints_.size(); i++) {
		localA.setIdentity();
		localB.setIdentity();

		localA.getBasis().setEulerZYX(0,SIMD_PI/2,0);
		localB.getBasis().setEulerZYX(0,SIMD_PI/2,0);

		localA.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(shape_radius*2)));
		localB.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(-shape_radius*2)));
		
		m_joints_[i] = new btHingeConstraint(*(m_bodies_[i]), *(m_bodies_[i+1]), localA, localB);
		m_joints_[i]->setLimit(btScalar(-SIMD_PI*0.15), btScalar(SIMD_PI*0.15));
	}
}


WormBulletCreature::~WormBulletCreature(void){
	for(int i=0; i < m_joints_.size(); i++){
		delete m_joints_[i];
		m_joints_[i] = 0;
	}

	for(int i=0; i < m_bodies_.size(); i++){
		delete m_bodies_[i]->getMotionState();
		delete m_bodies_[i];
		m_bodies_[i] = 0;
	}
	delete m_shape_;
}

void WormBulletCreature::AddToDynamicsWorld(btDiscreteDynamicsWorld* world){
	//Add bodies
	for(int i=0; i < m_bodies_.size(); i++){
		world->addRigidBody(m_bodies_[i]);

	}
	//Add joints
	btTransform localA, localB;
	for(int i=0; i < m_joints_.size(); i++){
		world->addConstraint(m_joints_[i], true);
	}
}

void WormBulletCreature::RemoveFromDynamicsWorld(btDiscreteDynamicsWorld* dynamics_world){
	for(int i=0; i < m_joints_.size(); i++){
		dynamics_world->removeConstraint(m_joints_[i]);
	}

	for(int i=0; i < m_bodies_.size(); i++){
		dynamics_world->removeRigidBody(m_bodies_[i]);
	}
}

void WormBulletCreature::UpdateMovement(float time)
{
	float max_impulse = 10.0;
	float max_velocity = 20;
	float max_a_velocity = 3.0;
	float max_a_phase = 2*SIMD_PI;

	for(int i=0; i < m_joints_.size(); i++){
		float velocity = max_velocity*genes_[i*4];
		float a_velocity = max_a_velocity*genes_[i*4 + 1];
		float a_phase = max_a_phase*genes_[i*4 + 2];
		float impulse = max_impulse*genes_[i*4 + 3];

		m_joints_[i]->enableAngularMotor(true, velocity*sin(a_velocity*time + a_phase) , impulse);
	}
}

btVector3 WormBulletCreature::GetCenterOfMass(){
	btVector3 center_of_mass = btVector3(0.0,0.0,0.0);
	for(int i=0; i < m_bodies_.size(); i++)
	{
		btTransform trans;
		m_bodies_[i]->getMotionState()->getWorldTransform(trans);

		center_of_mass += trans.getOrigin();
	}
	center_of_mass /= m_bodies_.size();

	return center_of_mass;
}

std::vector<btRigidBody*> WormBulletCreature::GetRigidBodies() {
	return m_bodies_;
}
