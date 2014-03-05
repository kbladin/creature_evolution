#include "Renderer.h"
#include <GL/glew.h>


Renderer::Renderer(Simulation* sim, bool debug_mode)
{
	dynamicsWorld = sim->GetDynamicsWorld();
	debugDrawer = new DebugDraw(dynamicsWorld);
	debug = debug_mode;
}


Renderer::~Renderer(void)
{
	delete debugDrawer;
}

void Renderer::render()
{
	if(debug)
	{
		debugDrawer->drawWorld();
	}
}
