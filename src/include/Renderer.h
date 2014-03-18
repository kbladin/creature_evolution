#ifndef RENDERER_H
#define RENDERER_H

#include <SceneManager.h>

class Renderer
{

public:
	Renderer(SceneManager* scene);
	~Renderer(void);
    
	void render();
private:
	SceneManager* scene_manager_;
};

#endif // RENDERER_H
