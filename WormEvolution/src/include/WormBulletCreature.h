#ifndef WORMBULLETCREATURE_H
#define WORMBULLETCREATURE_H

#include <vector>

#include <btBulletDynamicsCommon.h>

#include "Creature.h"

class WormBulletCreature {
public:
	WormBulletCreature(const std::vector<float> genes, btDiscreteDynamicsWorld* world, const btVector3& position);
	~WormBulletCreature(void);
	void updateMovement(float time);
	btVector3 getCenterOfMass();
private:
	btDiscreteDynamicsWorld* dynamics_world_;
	btCollisionShape* m_shape_;
	btScalar mass_;
	std::vector<btRigidBody*> m_bodies_;
	std::vector<btHingeConstraint*> m_joints_;
	std::vector<float> genes_;
};

#endif // WORMBULLETCREATURE_H