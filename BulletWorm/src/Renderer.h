#ifndef RENDERER_H
#define RENDERER_H

#include <linearmath/btidebugdraw.h>
#include "Simulation.h"
#include "debugDraw.h"

class Renderer
{

public:
	Renderer(Simulation* sim, bool debug_mode);
	~Renderer(void);
	void render();

private:
	bool debug;
	btDiscreteDynamicsWorld* dynamicsWorld;
	DebugDraw* debugDrawer;

};

#endif // RENDERER_H
