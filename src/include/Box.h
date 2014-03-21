#ifndef BOX_H
#define BOX_H

// C++
#include <iostream>
// Internal
#include "Shape.h"

class Box : public Shape {
public:
  Box();
  Box(float scale_x, float scale_y, float scale_z);
};

#endif //BOX_H