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
    BulletCreature(Creature*);
    ~BulletCreature(void);
    void UpdateMotors(std::vector<float> input);
    btVector3 GetCenterOfMass();
    std::vector<btRigidBody*> GetRigidBodies();
    std::vector<btHingeConstraint*> GetJoints();
private:
    btCollisionShape* m_shape_;
    btScalar mass_;
    std::vector<btRigidBody*> m_bodies_;
    std::vector<btHingeConstraint*> m_joints_;
    Creature* blueprint_;
};


#endif // BULLETCREATURE_H
