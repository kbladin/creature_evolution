#include "WormBulletCreature.h"


WormBulletCreature::WormBulletCreature(int segment_count, btDiscreteDynamicsWorld* world, const btVector3& position)
{
	dynamics_world_ = world;

	btScalar shape_radius = 0.1;
	m_shape_ = new btSphereShape(shape_radius);
	mass_ = 1;
	btVector3 localInertia(0,0,0);
	m_shape_->calculateLocalInertia(mass_,localInertia);

	//world position
	btTransform offset; offset.setIdentity();
	offset.setOrigin(position);

	//setup segments
	btTransform transform;
	for(int i=0; i < segment_count; i++)
	{
		//segments relative position
		transform.setIdentity();
		transform.setOrigin(btVector3(btScalar(0.), btScalar(i*shape_radius*SIMD_EPSILON), btScalar(0.)));
		btDefaultMotionState* myMotionState = new btDefaultMotionState(offset*transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass_,myMotionState,m_shape_,localInertia);
		rbInfo.m_additionalDamping = true;
		m_bodies_.push_back(btRigidBody(rbInfo));

		dynamics_world_->addRigidBody(&(m_bodies_[i]));

	/*	//damping
		m_bodies_[i].setDamping(0.05f, 0.85f);
		m_bodies_[i].setDeactivationTime(0.8f);
		m_bodies_[i].setSleepingThresholds(1.6f, 2.5f);*/
	}
	/*
	//setup joints
	btTransform localA, localB;
	bool useLinearReferenceFrameA = true;
	for(int i=0; i < segment_count-1; i++)
	{
		localA.setIdentity(); localB.setIdentity();
		localA.setOrigin(btVector3(btScalar(0.), btScalar(i*shape_radius), btScalar(0.)));
		localB.setOrigin(btVector3(btScalar(0.), btScalar((i+1)*shape_radius), btScalar(0.)));
		
		m_joints_.push_back(btGeneric6DofConstraint(m_bodies_[i], m_bodies_[i+1], localA, localB,useLinearReferenceFrameA));
		m_joints_[i].setAngularLowerLimit(btVector3(-SIMD_PI*0.3f,-SIMD_EPSILON,-SIMD_PI*0.3f));
		m_joints_[i].setAngularUpperLimit(btVector3(SIMD_PI*0.5f,SIMD_EPSILON,SIMD_PI*0.3f));

		
		dynamics_world_->addConstraint(&m_joints_[i], true);
	}*/
}


WormBulletCreature::~WormBulletCreature(void)
{
	delete m_shape_;

	for(int i=0; i < m_bodies_.size(); i++)
	{
		dynamics_world_->removeRigidBody(&m_bodies_[i]);
		delete m_bodies_[i].getMotionState();
	}

	for(int i=0; i < m_joints_.size(); i++)
	{
		dynamics_world_->removeConstraint(&m_joints_[i]);
	}
}