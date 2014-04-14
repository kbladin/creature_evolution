#ifndef PLANE_H
#define PLANE_H

// External
#ifndef Q_MOC_RUN
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#endif
// Internal
#include "Shape.h"

class Plane : public Shape {
public:
  Plane();
  Plane(glm::vec3 scale);
private:
  void SetupVertexPositionData();
  void SetupVertexNormalData();
  void SetupVertexUVData();
  void SetupElementData();
};

#endif // PLANE_H