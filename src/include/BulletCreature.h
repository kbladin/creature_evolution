#ifndef BULLETCREATURE_H
#define BULLETCREATURE_H

// C++
#include <iostream>
#include <vector>
// External
#include <btBulletDynamicsCommon.h>
// Internal
#include "Entity.h"
#include "Creature.h"
#include "Node.h"
#include "Shape.h"

class BulletCreature : public Entity {
public:
    BulletCreature(Creature);
    BulletCreature(Creature blueprint, float x_displacement, bool construct_nodes_);
    
    ~BulletCreature(void);
    void UpdateMotors(std::vector<float> input);
    btVector3 GetCenterOfMass();
    std::vector<btRigidBody*> GetRigidBodies();
    std::vector<btHingeConstraint*> GetJoints();
    btRigidBody* GetHead();
    virtual void Draw();
    virtual void Update();
    Creature GetCreature();

    void CollectData();

private:
    std::vector<btScalar> mass_;
    std::vector<btCollisionShape*> m_shapes_;
    std::vector<btRigidBody*> m_bodies_;
    std::vector<btHingeConstraint*> m_joints_;
    Creature blueprint_;

    bool construct_nodes_;
    std::vector<Node*> nodes_;


    btRigidBody* AddBody(BodyTree body, btVector3 position);

};


#endif // BULLETCREATURE_H
