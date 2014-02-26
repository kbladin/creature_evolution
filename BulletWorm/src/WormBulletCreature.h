#ifndef WORMBULLETCREATURE_H
#define WORMBULLETCREATURE_H

#include <vector>

#include <btBulletDynamicsCommon.h>


class WormBulletCreature
{
public:
	WormBulletCreature(int segment_count, btDiscreteDynamicsWorld* world, const btVector3& position);
	~WormBulletCreature(void);
	void updateMovement(float time);
private:
	btDiscreteDynamicsWorld* dynamics_world_;
	btCollisionShape* m_shape_;
	btScalar mass_;
	std::vector<btRigidBody*> m_bodies_;
	std::vector<btHingeConstraint*> m_joints_;
};

#endif // WORMBULLETCREATURE_H