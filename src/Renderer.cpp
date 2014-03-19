#include "Renderer.h"
#include <GL/glew.h>
#include <iostream>
Renderer::Renderer(SceneManager* scene)
{
	scene_manager_ = scene;
}


Renderer::~Renderer(void)
{
}

void Renderer::render()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene_manager_->RenderNodes();
}
