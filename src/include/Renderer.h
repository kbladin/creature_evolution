#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
// C++
#include <iostream>

// Internal
#include "SceneManager.h"

class Renderer
{

public:
	Renderer() { };
	Renderer(SceneManager* scene);
	~Renderer(void);
    void Init();
	void render();
private:
	SceneManager* scene_manager_;
};

#endif // RENDERER_H
