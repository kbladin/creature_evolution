#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <Shape.h>
class Node {
  public:
    Node(glm::mat4 transform);
    void SetShape(Shape shape);
    void Render(glm::mat4 view, glm::mat4 projection);
    void SetTransform(glm::mat4 trans);
    glm::mat4 GetTransform();
  private:
    glm::mat4 transform_;
    Shape shape_;
};

#endif //NODE_H