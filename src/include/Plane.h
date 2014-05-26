#ifndef PLANE_H
#define PLANE_H

// External
#ifndef Q_MOC_RUN
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#endif
// Internal
#include "Shape.h"

//! Used in the render process. A plane to render.
/*!
  This class extends Shape and it therefore a containter of all the vertex data
  used by OpenGL in the rendering process.
*/
class Plane : public Shape {
public:
  Plane();
  Plane(glm::vec3 scale);
  Plane(glm::vec3 scale, glm::vec4 plane_equation);
private:
  void SetupVertexPositionData();
  void SetupVertexNormalData();
  void SetupVertexUVData();
  void SetupElementData();
};

#endif // PLANE_H
