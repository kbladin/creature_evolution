#include "DebugDraw.h"

DebugDraw::DebugDraw(btDiscreteDynamicsWorld* world)
{
	dynamicsWorld = world;
	dynamicsWorld->setDebugDrawer(this);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    // An array of 3 vectors which represents 3 vertices
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    
    glGenBuffers(1, &vertexbuffer);

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
    
    
    btCollisionObjectArray& collisionObjects = dynamicsWorld->getCollisionObjectArray();
    //for loop
    for (int i=0; i<collisionObjects.size(); ++i) {
        btCollisionObject* colObj = collisionObjects[i];
        btTransform trans = colObj->getWorldTransform();
        btVector3 position_origin = trans.getOrigin();
        
        lines_.push_back(position_origin.x());
        lines_.push_back(position_origin.y());
        lines_.push_back(position_origin.z());
    }
}

void DebugDraw::BufferSetup() {
}

void DebugDraw::DrawBuffers() {
    
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lines_.size(), &lines_[0], GL_STATIC_DRAW);
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                          0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    // Draw the triangle !
    glDrawArrays(GL_POINTS, 0, lines_.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
    
    glDisableVertexAttribArray(0);
    
	lines_.clear();
	lines_.resize(0);
}