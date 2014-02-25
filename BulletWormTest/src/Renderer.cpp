#include "Renderer.h"
#include <GL/glew.h>


Renderer::Renderer(Simulation* sim)
{
	dynamicsWorld = sim->getDynamicsWorld();
	debugDrawer = new DebugDraw(dynamicsWorld);
	debug = true;
}


Renderer::~Renderer(void)
{
	delete debugDrawer;
}

void Renderer::render()
{
	if(debug)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		debugDrawer->drawWorld();
	}
}
