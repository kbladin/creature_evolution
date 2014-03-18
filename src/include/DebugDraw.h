#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <LinearMath/btIDebugDraw.h>
#include "Simulation.h"
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


class DebugDraw{
    
int m_debugMode;

public:
	DebugDraw(btDiscreteDynamicsWorld* world);
	virtual ~DebugDraw(void);
    
    void SetupMatrices(GLuint shader);

    virtual void    setDebugMode(int debugMode){m_debugMode = debugMode;};
	virtual int     getDebugMode() const { return m_debugMode;}

	void drawWorld();
	void BufferSetup();
	void DrawBuffers();

private:
	btDiscreteDynamicsWorld* dynamicsWorld;
    
    GLuint VertexArrayID;
    GLuint vertexbuffer;
    // Matrices
    GLuint M_loc_, V_loc_, MV_loc_, MVP_loc_;
	
    std::vector<float> lines_;
};

#endif // DEBUGDRAW_H
