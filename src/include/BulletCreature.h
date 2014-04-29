#ifndef BULLETCREATURE_H
#define BULLETCREATURE_H

// C++
#include <iostream>
#include <vector>
// External
#include <btBulletDynamicsCommon.h>
// Internal
#include "Creature.h"

class BulletCreature {
public:
    BulletCreature(Creature);
    BulletCreature(Creature blueprint, float x_displacement);
    
    ~BulletCreature(void);
    void UpdateMotors(std::vector<float> input);
    btVector3 GetCenterOfMass();
    std::vector<btRigidBody*> GetRigidBodies();
    std::vector<btHingeConstraint*> GetJoints();
    btRigidBody* GetHead();
    Creature GetCreature();

    void CollectData();

private:
    // Should these be put in a struct?
    std::vector<btScalar> mass_;
    std::vector<btCollisionShape*> m_shapes_;
    std::vector<btRigidBody*> m_bodies_;
    std::vector<btHingeConstraint*> m_joints_;
    Creature blueprint_;
    std::vector<btScalar> joint_strength_;


    btRigidBody* AddBody(BodyTree body, btVector3 position);

};


#endif // BULLETCREATURE_H
