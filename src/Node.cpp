#include "Node.h"
#include "Camera.h"
#include <iostream>

//! Creating a Node from a btRigidBody.
/*!
  Depending on the shape of the btRigidBody, a Shape for rendering is
  created.
  \param body is the btRigifBody pointer from which to create the Node.
*/
Node::Node(btRigidBody* body) {
  rigid_body_ = body;
  //init transform
  UpdateNode();
  //init shape
  int shape_type = rigid_body_->getCollisionShape()->getShapeType();
  switch(shape_type) {
  case BOX_SHAPE_PROXYTYPE:
    InitBoxShape();
    break;
  case STATIC_PLANE_PROXYTYPE:
    InitPlaneShape();
    break;
  case SPHERE_SHAPE_PROXYTYPE:
    InitSphereShape();//no sphere implemented yet
    break;
  default:
    shape_ = Box();
    break;
  }
  shape_.SetupBuffers();
}

void Node::DebugPrint() {
  std::cout << "Node transform: " << glm::to_string(transform_)
      << std::endl;
}

//! Setting the transform of the Node
/*!
  \param transform is transform to set.
*/
void Node::SetTransform(glm::mat4 transform) {
  transform_ = transform;
}

//! Setting the position of the Node by updating the transform
/*!
  \param pos is the position to set.
*/
void Node::SetPosition(glm::vec3 pos) {
  transform_ = glm::translate(glm::mat4(1.0f), pos);
}

//! Getting the position of the Node by using the transform of the rigid body.
/*!
  \return the position of the Node.
*/
glm::vec3 Node::GetPosition() {
    float x = rigid_body_->getWorldTransform().getOrigin().getX();
    float y = rigid_body_->getWorldTransform().getOrigin().getY();
    float z = rigid_body_->getWorldTransform().getOrigin().getZ();
    return glm::vec3(x,y,z);
}

//! Render the Node using the camera specified.
/*!
  In this function; the Shape corresponding to the Node will be rendered with
  its specific render function.
  \param camera is the camera used for rendering (believe it or not).
*/
void Node::Render(Camera* camera) {
  shape_.Render(camera, transform_);
}

//! Setting the transform of the Node from the transform of the rigid body associated with it.
void Node::UpdateNode(){
    btTransform transform;
    transform = rigid_body_->getWorldTransform();
    glm::mat4 tmp_matrix;
    transform.getOpenGLMatrix(glm::value_ptr(tmp_matrix));
    transform_ = tmp_matrix;
}

//! Internal function making the Shape a Box from the dimensions of the rigid body.
void Node::InitBoxShape() {
    btBoxShape* boxShape = (btBoxShape*)(rigid_body_->getCollisionShape());
    btVector3 v;
    boxShape->getVertex(0,v);

    shape_ = Box(v.getX(),v.getY(),v.getZ());
}

//! Internal function making the Shape a Plane from the dimensions of the rigid body.
void Node::InitPlaneShape() {
    btStaticPlaneShape* planeShape = (btStaticPlaneShape*)(rigid_body_->getCollisionShape());
    btVector3 normal = planeShape->getPlaneNormal();
    float constant = planeShape->getPlaneConstant();
    glm::vec4 plane_equation = glm::vec4(normal.getX(),normal.getY(),normal.getZ(),constant);
    shape_ = Plane(glm::vec3(1.0f) * 200.0f, plane_equation);
}

//! Internal function making the Shape a Sphere from the dimensions of the rigid body.
/*!
  Not implemented.
*/
void Node::InitSphereShape() {

}

//! Deleting the OpenGL-buffers in the Shape.
void Node::DeleteBuffers() {
  shape_.DeleteBuffers();
}
