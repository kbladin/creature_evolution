#ifndef CREATURE_H
#define CREATURE_H

#include <vector>

#include <btBulletDynamicsCommon.h>

class Creature
{
public:
	Creature(void);
	virtual ~Creature(void);
	virtual void Mutate() = 0;
	virtual std::vector<Creature> Mate(Creature& mate) = 0;
};

#endif // CREATURE_H

