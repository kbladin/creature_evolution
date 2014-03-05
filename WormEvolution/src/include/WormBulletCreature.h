#ifndef WORMBULLETCREATURE_H
#define WORMBULLETCREATURE_H

#include <cmath>
#include <iostream>
#include <vector>
#include <btBulletDynamicsCommon.h>

class WormBulletCreature {
public:
	WormBulletCreature(const std::vector<float> genes, const btVector3& position);
	~WormBulletCreature(void);
	void AddToDynamicsWorld(btDiscreteDynamicsWorld* world);
	void RemoveFromDynamicsWorld(btDiscreteDynamicsWorld* world);
	void UpdateMovement(float time);
	btVector3 GetCenterOfMass();
	float GetFitnessValue();
private:
	btCollisionShape* m_shape_;
	btScalar mass_;
	std::vector<btRigidBody*> m_bodies_;
	std::vector<btHingeConstraint*> m_joints_;
	std::vector<float> genes_;
};

#endif // WORMBULLETCREATURE_H