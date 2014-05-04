#include "BulletCreature.h"
#include "Box.h"
#include "Scene.h"

BulletCreature::BulletCreature(Creature blueprint) {
    //connect brain
    blueprint_ = blueprint;
    blueprint_.simdata.ResetData();

    //create body
    BodyTree body_root = blueprint_.GetBody().GetBodyRoot();
    AddBody(body_root, btVector3(0.0,-body_root.GetLowestPoint(),0.0));
}


BulletCreature::BulletCreature(Creature blueprint, float x_displacement) {

    //connect brain
    blueprint_ = blueprint;

    //create body
    BodyTree body_root = blueprint_.GetBody().GetBodyRoot();
    AddBody(body_root, btVector3(x_displacement,-body_root.GetLowestPoint(),0.0));

}


BulletCreature::~BulletCreature(void) {
    while(!m_joints_.empty()) {
      delete m_joints_.back();
      m_joints_.pop_back();
    }

    while(!m_bodies_.empty()) {
      delete m_bodies_.back()->getMotionState();
      delete m_bodies_.back();
      m_bodies_.pop_back();
    }

    while(!m_shapes_.empty()) {
      delete m_shapes_.back();
      m_shapes_.pop_back();
    }


    m_joints_.clear();
    m_bodies_.clear();
    m_shapes_.clear();
}



btRigidBody* BulletCreature::AddBody(BodyTree body, btVector3 position) {
    //shape
    btVector3 dim = btVector3(body.box_dim.x,body.box_dim.y,body.box_dim.z);
    btCollisionShape* shape = new btBoxShape(dim);

    btVector3 fallInertia(0,0,0);
    float mass = body.GetMass();
    shape->calculateLocalInertia(mass,fallInertia);

    //body
    btTransform offset;
    offset.setIdentity();
    offset.setOrigin(position);

    btMotionState* motion_state;

    motion_state = new btDefaultMotionState(offset);

    btRigidBody::btRigidBodyConstructionInfo rigid_body(mass,motion_state,shape,fallInertia);
    btRigidBody* current_body = new btRigidBody(rigid_body);
    
    current_body->setFriction(body.friction);

    // Add data
    m_bodies_.push_back(current_body);
    mass_.push_back(mass);
    m_shapes_.push_back(shape);    

    //add children
    Joint joint;
    btTransform localA, localB;
    for(int i=0; i<body.body_list.size(); i++) {
        //child position
        joint = body.body_list[i].root_joint;
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
        btHingeConstraint* hinge = new btHingeConstraint(*(current_body), *(child_body), localA, localB);
        m_joints_.push_back(hinge);

        // For now just proportional to the mass of the bodies,
        // seems to be what works best for most creatures.
        float strength = (body.body_list[i].root_joint.strength < 0) ?
                    body.GetMass() + body.body_list[i].GetMass() :
                    body.body_list[i].root_joint.strength;

        joint_strength_.push_back(strength);
        m_joints_.back()->setLimit(
                        btScalar(joint.lower_limit),
                        btScalar(joint.upper_limit),
                        0.9, // Softness = 0.9 default
                        0.3, // Bias factor = 0.3 default
                        1.0); // Relaxation factor = 1.0 default
    }
    return current_body;
}


void BulletCreature::UpdateMotors(std::vector<float> input) {
    std::vector<float> signal = blueprint_.CalculateBrainOutput(input);

    for(int i=0; i < m_joints_.size(); i++) {

        int sign = signal[i] < 0 ? -1 : 1;
        float impulse = joint_strength_[i]*sign*signal[i];
        m_joints_[i]->enableAngularMotor(
                    true,
                    1000000.0*sign,
                    impulse); // apply force
        
        //update creatures energy for every joint..
        blueprint_.simdata.energy_waste += impulse;
    }
}

btVector3 BulletCreature::GetCenterOfMass(){
    btVector3 center_of_mass = btVector3(0.0,0.0,0.0);
    float mass_sum = 0.0;
    for(int i=0; i < m_bodies_.size(); i++) {
        center_of_mass += m_bodies_[i]->getCenterOfMassPosition() * mass_[i];
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

btVector3 BulletCreature::GetHeadPosition() {
    return m_bodies_[0]->getCenterOfMassPosition();
}

Creature BulletCreature::GetCreature() {
    return blueprint_;
}

void BulletCreature::CollectData(std::vector<float> sim_data) {
    SimData data = blueprint_.simdata;

    data.distance_light = sim_data.front();
    data.distance_z = GetCenterOfMass().getZ();
    data.max_y = (GetCenterOfMass().getY() > data.max_y) ?
                    GetCenterOfMass().getY() : data.max_y;
    data.accumulated_y += GetCenterOfMass().getY();
    data.deviation_x = abs(GetCenterOfMass().getX())+0.0001;
    data.accumulated_head_y += GetHeadPosition().getY();

    blueprint_.simdata = data;
}
