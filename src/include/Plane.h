#ifndef PLANE_H
#define PLANE_H

#include <Shape.h>
#include <glm/glm.hpp>

class Plane : public Shape {
public:
	Plane(glm::vec3 scale);
};

#endif // PLANE_H