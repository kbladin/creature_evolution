#ifndef BOX_H
#define BOX_H

#include <Shape.h>

class Box : public Shape {
public:
  Box(glm::vec3 scale);
};

#endif //BOX_H