#include "BulletCreature.h"

BulletCreature::BulletCreature(Creature* blueprint) {
    blueprint_ = blueprint;
    //init body, this should either use data from Creature->Body or be done in Body
    //world position
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(btVector3(0.0,0.0,0.0));

    //setup segments
    btScalar scale = 0.1;
    m_shape_ = new btBoxShape(btVector3(scale*2,scale,scale*2));
    mass_ = 5;
    btVector3 fallInertia(0,0,0);
    m_shape_->calculateLocalInertia(mass_,fallInertia);

    btDefaultMotionState* motion_state;
    btTransform transform;

    m_bodies_.resize(6);
    m_joints_.resize(5);
    for(int i=0; i < m_bodies_.size(); i++) {
        transform.setIdentity();
        transform.setOrigin(btVector3(btScalar(0.), btScalar(0.0), btScalar(i*scale*2)));

        motion_state = new btDefaultMotionState(offset*transform);
        btRigidBody::btRigidBodyConstructionInfo rigid_body(mass_,motion_state,m_shape_,fallInertia);
        m_bodies_[i] = new btRigidBody(rigid_body);
        m_bodies_[i]->setFriction(0.5f);
    }

    //setup joints
    btTransform localA, localB;
    for(int i=0; i < m_joints_.size(); i++) {
        localA.setIdentity();
        localB.setIdentity();

        localA.getBasis().setEulerZYX(0,SIMD_PI/2,0);
        localB.getBasis().setEulerZYX(0,SIMD_PI/2,0);

        localA.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(scale*2)));
        localB.setOrigin(btVector3(btScalar(0.), btScalar(0.), btScalar(-scale*2)));

        m_joints_[i] = new btHingeConstraint(*(m_bodies_[i]), *(m_bodies_[i+1]), localA, localB);
        m_joints_[i]->setLimit(btScalar(-SIMD_PI*0.2), btScalar(SIMD_PI*0.2));
    }
}

BulletCreature::~BulletCreature(void) {
    for(int i=0; i < m_joints_.size(); i++){
        delete m_joints_[i];
        m_joints_[i] = 0;
    }

    for(int i=0; i < m_bodies_.size(); i++){
        delete m_bodies_[i]->getMotionState();
        delete m_bodies_[i];
        m_bodies_[i] = 0;
    }
}

void BulletCreature::UpdateMotors(std::vector<float> input) {
    std::vector<float> signal = blueprint_->CalculateBrainOutput(input);

    for(int i=0; i < m_joints_.size(); i++) {
        m_joints_[i]->enableAngularMotor(true, 20.0*signal[i], 10.0);
    }
}

btVector3 BulletCreature::GetCenterOfMass(){
    btVector3 center_of_mass = btVector3(0.0,0.0,0.0);
    for(int i=0; i < m_bodies_.size(); i++) {
        btTransform trans;
        m_bodies_[i]->getMotionState()->getWorldTransform(trans);
        center_of_mass += trans.getOrigin();
    }
    center_of_mass /= m_bodies_.size();

    return center_of_mass;
}

std::vector<btRigidBody*> BulletCreature::GetRigidBodies() {
    return m_bodies_;
}

std::vector<btHingeConstraint*> BulletCreature::GetJoints() {
    return m_joints_;
}
