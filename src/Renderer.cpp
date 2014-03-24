#include <GL/glew.h>
#include "Renderer.h"

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

void Renderer::Init() {

	glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
	scene_manager_->InitShapes();
}
