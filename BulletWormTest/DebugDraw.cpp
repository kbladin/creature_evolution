#include "DebugDraw.h"
#include "GL/glew.h"
#include "Simulation.h"


DebugDraw::DebugDraw(btDiscreteDynamicsWorld* world)
{
	dynamicsWorld = world;
	dynamicsWorld->setDebugDrawer(this);
}


DebugDraw::~DebugDraw(void)
{
}

void DebugDraw::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
    glBegin(GL_LINES);
        glColor3f(color.getX(), color.getY(), color.getZ());
        glVertex3d(from.getX(), from.getY(), from.getZ());
        glVertex3d(to.getX(), to.getY(), to.getZ());
    glEnd();
}

void DebugDraw::drawWorld()
{
	dynamicsWorld->debugDrawWorld();
}