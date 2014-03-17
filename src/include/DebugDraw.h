#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <LinearMath/btIDebugDraw.h>
#include "Simulation.h"
#include <GL/glew.h>
#include <GL/glfw3.h>


class DebugDraw :
	public btIDebugDraw
{
int m_debugMode;

public:
	DebugDraw(btDiscreteDynamicsWorld* world);
	virtual ~DebugDraw(void);

	virtual void    drawLine(const btVector3& from,const btVector3& to,
			const btVector3& color);

	virtual void    drawContactPoint(const btVector3& PointOnB,
			const btVector3& normalOnB,btScalar distance,int lifeTime,
			const btVector3& color){return;};

	virtual void    reportErrorWarning(const char* warningString){return;};

	virtual void    draw3dText(const btVector3& location,const char* textString)
		{return;};

	virtual void    setDebugMode(int debugMode){m_debugMode = debugMode;};

	virtual int     getDebugMode() const { return m_debugMode;}

	void drawWorld();
	void BufferSetup();
	void DrawBuffers();

private:
	btDiscreteDynamicsWorld* dynamicsWorld;
    
    GLuint VertexArrayID;
    GLuint vertexbuffer;

	//unsigned int vbo_;
	//unsigned int vao_;

	std::vector<float> lines_;
};

#endif // DEBUGDRAW_H
