#include "DebugDraw.h"
#include "Simulation.h"
#include <GL/glew.h>

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
	lines_.push_back(from.getX());
	lines_.push_back(from.getY());
	lines_.push_back(from.getZ());

	lines_.push_back(to.getX());
	lines_.push_back(to.getY());
	lines_.push_back(to.getZ());
}

void DebugDraw::drawWorld()
{
	dynamicsWorld->debugDrawWorld();
}

void DebugDraw::BufferSetup() {
	vbo_ = 0;
	glGenBuffers (1, &vbo_);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_);
	glBufferData (GL_ARRAY_BUFFER, lines_.size() * sizeof (float), &lines_[0], GL_STATIC_DRAW);

	vao_ = 0;
	glGenVertexArrays (1, &vao_);
	glBindVertexArray (vao_);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}

void DebugDraw::DrawBuffers() {
	glBindVertexArray (vao_);
	glDrawArrays (GL_LINES, 0, lines_.size());

	glDisableVertexAttribArray(0);
	lines_.clear();
	lines_.resize(0);
}