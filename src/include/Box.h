#ifndef BOX_H
#define BOX_H

// C++
#include <iostream>
// Internal
#include "TextureManager.h"
#include "Shape.h"


//! Used in the render process. A box to render.
/*!
  This class extends Shape and it therefore a containter of all the vertex data
  used by OpenGL in the rendering process.
*/
class Box : public Shape {
public:
  Box(Material material);
  Box(float scale_x, float scale_y, float scale_z, Material material);
private:
  void SetupVertexPositionData();
  void SetupVertexNormalData();
  void SetupVertexUVData();
  void SetupElementData();
};

#endif  // BOX_H
