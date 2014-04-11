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

class Node {
public:
  Node();
  void InitShape();
  void SetShape(Shape shape);
  void Render(Camera camera);
  void SetTransform(glm::mat4 trans);
  void SetPosition(glm::vec3 pos);
  glm::mat4 GetTransform();
  void DebugPrint();
  virtual void UpdateNode();
protected:
  glm::mat4 transform_;
  Shape shape_;
};

class PhysicsNode : public Node {
public:
  PhysicsNode();
  PhysicsNode(btRigidBody* rigid_body);
  void UpdateNode();
private:
  btRigidBody* rigid_body_;
};

#endif //NODE_H