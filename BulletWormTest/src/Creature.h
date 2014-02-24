#ifndef CREATURE_H
#define CREATURE_H

#include <btBulletDynamicsCommon.h>

class Creature
{
public:
	Creature(void);
	~Creature(void);
	void spawnBulletCreature(const btVector3& startOffset);
};

#endif // CREATURE_H

