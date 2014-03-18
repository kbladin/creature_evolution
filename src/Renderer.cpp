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

void calcMatrices(){
    
}

void Renderer::render(GLuint shader_id)
{
    glUseProgram(shader_id);
	if(debug)
	{
		debugDrawer->drawWorld();
		debugDrawer->BufferSetup();
		debugDrawer->DrawBuffers();
	}
    glUseProgram(0);
}
