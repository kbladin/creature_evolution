#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Camera.h>

class Shape {
public:
  void Render(glm::mat4 model_transform, Camera camera);
protected:
  GLuint vertex_array_id_;
  GLuint vertex_buffer_position_id_;
  std::vector<glm::vec3> vertex_data_;
};

class Box : public Shape {
public:
  Box();
};

#endif // SHAPE_H