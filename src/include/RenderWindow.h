#include "OpenGLWindow.h"
#include "CreatureEvolution.h"

class RenderWindow : public OpenGLWindow
{
public:
    RenderWindow(CreatureEvolution* CE);
    ~RenderWindow();
    void initialize();
    void render();

private:
	CreatureEvolution* creature_evo_;

    int m_frame;
};
