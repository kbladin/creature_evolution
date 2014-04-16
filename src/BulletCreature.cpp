#include "BulletCreature.h"

BulletCreature::BulletCreature(Creature blueprint) {

    //connect brain
    blueprint_ = blueprint;

    //create body
    AddBody(blueprint_.GetBody().GetBodyRoot(), btVector3(0.0,1.5,0.0));

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

    for(int i=0; i < m_shapes_.size(); i++){
        delete m_shapes_[i];
        m_shapes_[i] = 0;
    }
}



btRigidBody* BulletCreature::AddBody(BodyTree body, btVector3 position) {
    //shape
    btVector3 dim = btVector3(body.box_dim.x,body.box_dim.y,body.box_dim.z);
    m_shapes_.push_back(new btBoxShape(dim));

    //mass
    btVector3 fallInertia(0,0,0);
    m_shapes_.back()->calculateLocalInertia(body.mass,fallInertia);
    mass_.push_back(body.mass);

    //body
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(position);
    btDefaultMotionState* motion_state = new btDefaultMotionState(offset);
    btRigidBody::btRigidBodyConstructionInfo rigid_body(mass_.back(),motion_state,m_shapes_.back(),fallInertia);
    btRigidBody* current_body = new btRigidBody(rigid_body);
    m_bodies_.push_back(current_body);
    //friction
    m_bodies_.back()->setFriction(body.friction);
    //add children
    Joint joint;
    btTransform localA, localB;
    for(int i=0; i<body.body_list.size(); i++) {
        //child position
        joint = body.joint_list[i];
        Vec3 c = joint.connection_root - joint.connection_branch;
        btVector3 child_offset(c.x,c.y,c.z);
        //body
        btRigidBody* child_body = AddBody(body.body_list[i],position+child_offset);
        //joint
        localA.setIdentity();
        localB.setIdentity();
        Vec3 h = joint.hinge_orientation;
        localA.getBasis().setEulerZYX(h.x,h.y,h.z);
        localB.getBasis().setEulerZYX(h.x,h.y,h.z);
        Vec3 a = joint.connection_root;
        Vec3 b = joint.connection_branch;
        localA.setOrigin(btVector3(a.x,a.y,a.z));
        localB.setOrigin(btVector3(b.x,b.y,b.z));
        m_joints_.push_back(new btHingeConstraint(*(current_body), *(child_body), localA, localB));
        m_joints_.back()->setLimit(btScalar(joint.lower_limit), btScalar(joint.upper_limit));

    }
    return current_body;
}


void BulletCreature::UpdateMotors(std::vector<float> input) {
    std::vector<float> signal = blueprint_.CalculateBrainOutput(input);

    int sign = 1;

    for(int i=0; i < m_joints_.size(); i++) {

        if(signal[i]>=0)
            sign=1;
        else
            sign=-1;

        m_joints_[i]->enableAngularMotor(true, 80.0*sign, 10.0*sign*signal[i]); // apply force
    }
}

btVector3 BulletCreature::GetCenterOfMass(){
    btVector3 center_of_mass = btVector3(0.0,0.0,0.0);
    float mass_sum = 0.0;
    for(int i=0; i < m_bodies_.size(); i++) {
        btTransform trans;
        m_bodies_[i]->getMotionState()->getWorldTransform(trans);
        center_of_mass += trans.getOrigin()*mass_[i];
        mass_sum += mass_[i];
    }
    center_of_mass /= mass_sum;

    return center_of_mass;
}

std::vector<btRigidBody*> BulletCreature::GetRigidBodies() {
    return m_bodies_;
}

std::vector<btHingeConstraint*> BulletCreature::GetJoints() {
    return m_joints_;
}

btRigidBody* BulletCreature::GetHead() {
    return m_bodies_[0];
}
