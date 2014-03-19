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
	//std::cout << "I'M INSIDE THE RENDERER!" << std::endl;
}
