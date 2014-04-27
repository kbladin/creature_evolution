#ifndef NODE_H
#define NODE_H

// C++
#include <iostream>
// External
#ifndef Q_MOC_RUN
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#endif
#include <btBulletDynamicsCommon.h>
// Internal
#include "Shape.h"
#include "Box.h"
#include "Plane.h"

class Camera;

class Node {
public:
  Node(btRigidBody* body);
  void Render(Camera* camera);
  void SetTransform(glm::mat4 trans);
  void SetPosition(glm::vec3 pos);
  glm::mat4 GetTransform();
  void DebugPrint();
  void UpdateNode();
private:
  void InitBoxShape();
  void InitPlaneShape();
  void InitSphereShape();

  glm::mat4 transform_;
  Shape shape_;
  btRigidBody* rigid_body_;
};

#endif //NODE_H
