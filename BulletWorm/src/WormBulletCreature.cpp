#include "WormBulletCreature.h"
#include <cmath>


WormBulletCreature::WormBulletCreature(int segment_count, btDiscreteDynamicsWorld* world, const btVector3& position)
{
	m_bodies_.resize(segment_count);
	m_joints_.resize(segment_count-1);
	dynamics_world_ = world;
	
	//world position
	btTransform offset;
	offset.setIdentity();
	offset.setOrigin(position);

	//setup segments
	btScalar shape_radius = 0.1;
	m_shape_ = new btSphereShape(shape_radius);
	mass_ = 1;
	btVector3 fallInertia(0,0,0);
	m_shape_->calculateLocalInertia(mass_,fallInertia);

	btDefaultMotionState* motion_state;
	btTransform transform;
	for(int i=0; i < segment_count; i++)
	{
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(i*shape_radius*2)));

		motion_state = new btDefaultMotionState(offset*transform);
		btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass_,motion_state,m_shape_,fallInertia);
		m_bodies_[i] = new btRigidBody(fallRigidBodyCI);
		dynamics_world_->addRigidBody(m_bodies_[i]);

		//damping
		//m_bodies_[i]->setDamping(0.05f, 0.85f);
		//m_bodies_[i]->setDeactivationTime(0.8f);
		//m_bodies_[i]->setSleepingThresholds(1.6f, 2.5f);
	}

	
	//setup joints
	btTransform localA, localB;
	for(int i=0; i < segment_count-1; i++)
	{
		localA.setIdentity();
		localB.setIdentity();
		localA.setOrigin(btVector3(btScalar(0.), btScalar(shape_radius), btScalar(0.)));
		localB.setOrigin(btVector3(btScalar(0.), btScalar(-shape_radius), btScalar(0.)));
		
		m_joints_[i] = new btHingeConstraint(*(m_bodies_[i]), *(m_bodies_[i+1]), localA, localB);
		m_joints_[i]->setLimit(btScalar(-SIMD_PI*0.01), btScalar(SIMD_PI*0.01));
		
		dynamics_world_->addConstraint(m_joints_[i], true);
	}
	m_joints_[segment_count/2]->enableAngularMotor(true, -1000.0f, 1000.0f);
}


WormBulletCreature::~WormBulletCreature(void)
{
	for(int i=0; i < m_joints_.size(); i++)
	{
		dynamics_world_->removeConstraint(m_joints_[i]);
		delete m_joints_[i];
		m_joints_[i] = 0;
	}

	for(int i=0; i < m_bodies_.size(); i++)
	{
		dynamics_world_->removeRigidBody(m_bodies_[i]);
		delete m_bodies_[i]->getMotionState();

		delete m_bodies_[i];
		m_bodies_[i] = 0;

		delete m_shape_;

	}
}

void WormBulletCreature::updateMovement(float time)
{
	for(int i=0; i < m_joints_.size(); i++)
	{
		m_joints_[i]->enableAngularMotor(true, 10*sin(time+i) , 1000.65f);
	}
}