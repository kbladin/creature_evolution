#include "DebugDraw.h"

DebugDraw::DebugDraw(btDiscreteDynamicsWorld* world)
{
	dynamicsWorld = world;

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    // An array of 3 vectors which represents 3 vertices
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    
    glGenBuffers(1, &vertexbuffer);
    
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
    glDisableVertexAttribArray(0);
    
}


DebugDraw::~DebugDraw(void)
{
}

void DebugDraw::SetupMatrices(GLuint shader_id){
    // ids
    MVP_loc_ = glGetUniformLocation( shader_id, "MVP");
    MV_loc_ = glGetUniformLocation( shader_id, "MV");
    V_loc_ = glGetUniformLocation( shader_id, "V");
    M_loc_ = glGetUniformLocation( shader_id, "M");
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
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * lines_.size(), &lines_[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DebugDraw::DrawBuffers() {
    
    glm::mat4 M = glm::mat4(1.0f);
    glm::mat4 V = glm::mat4(1.0f);
    glm::mat4 P = glm::perspective(40.0f, 4.0f/3.0f, 0.1f, 100.0f);
    
    glm::mat4 MV = V*M;
    glm::mat4 MVP = P*V*M;
    
    // Matrix data
    glUniformMatrix4fv(MVP_loc_, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(M_loc_, 1, GL_FALSE, &M[0][0]);
    glUniformMatrix4fv(MV_loc_, 1, GL_FALSE, &MV[0][0]);
    glUniformMatrix4fv(V_loc_, 1, GL_FALSE, &V[0][0]);
    
    glBindVertexArray(VertexArrayID);

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_POINTS, 0, lines_.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
    
    glDisableVertexAttribArray(0);

	lines_.clear();
	lines_.resize(0);
}