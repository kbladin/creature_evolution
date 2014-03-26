#ifndef RENDERER_H
#define RENDERER_H

// C++
#include <iostream>
// External
#include <GL/glew.h>
// Internal
#include "SceneManager.h"

class Renderer
{

public:
	Renderer() { };
	Renderer(SceneManager* scene);
	~Renderer(void);
    
	void render();
private:
	SceneManager* scene_manager_;
};

#endif // RENDERER_H
