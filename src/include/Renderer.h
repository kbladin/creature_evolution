#ifndef RENDERER_H
#define RENDERER_H

#include <LinearMath/btIDebugDraw.h>
#include "Simulation.h"
#include "DebugDraw.h"

class Renderer
{

public:
	Renderer(Simulation* sim, bool debug_mode);
	~Renderer(void);
    
	void render(GLuint shader_id);

private:
	bool debug;
	btDiscreteDynamicsWorld* dynamicsWorld;
	DebugDraw* debugDrawer;
};

#endif // RENDERER_H
