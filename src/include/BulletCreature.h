#ifndef BULLETCREATURE_H
#define BULLETCREATURE_H

// C++
#include <iostream>
#include <vector>
// External
#include <btBulletDynamicsCommon.h>
// Internal
#include "Creature.h"

//! This class describes a creature which is used in the physics simulation
/*!
  From the Creature class, which is defined by a Body and a Brain; a
  BulletCreature can be created. This class transfer the data and sets it up
  in a way that the physics library Bullet understands.
*/
class BulletCreature {
public:
  // Constructors
  BulletCreature(Creature);
  BulletCreature(Creature blueprint, float x_displacement);
  
  // Destructor
  ~BulletCreature(void);

  // Getters
  btVector3 GetCenterOfMass();
  std::vector<btRigidBody*> GetRigidBodies();
  std::vector<Material> GetMaterials();
  std::vector<btHingeConstraint*> GetJoints();
  btRigidBody* GetHead();
  btVector3 GetHeadPosition();
  Creature GetCreature();
  float GetDistanceToLight();

  // Setters
  void SetDistanceToLight(float distance);
  void CollectData();
  void UpdateMotors(std::vector<float> input);
private:
  // Fitness data from world
  float distance_to_light_;

  // Should these be put in a struct?
  std::vector<btScalar> mass_;
  std::vector<btCollisionShape*> m_shapes_;
  std::vector<btRigidBody*> m_bodies_;
  std::vector<Material> materials_;
  std::vector<btHingeConstraint*> m_joints_;
  std::vector<btScalar> joint_strength_;

  Creature blueprint_;

  btRigidBody* AddBody(BodyTree body, btVector3 position);
  int brain_counter_;
};


#endif // BULLETCREATURE_H
