#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#include <btBulletDynamicsCommon.h>

#include <Shape.h>
class Node {
  public:
    Node();
    void SetShape(Shape shape);
    void Render(Camera camera);
    void SetTransform(glm::mat4 trans);
    void SetPosition(glm::vec3 pos);
    glm::mat4 GetTransform();
    void DebugPrint();
  
  private:
    glm::mat4 transform_;
    Shape shape_;
};

class PhysicsNode : public Node {
public:
    void UpdateNodeFromBullet();
private:
    btRigidBody* rigid_body_;
};


#endif //NODE_H