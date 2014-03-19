#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <Camera.h>

class Shape {
public:
	Shape() { };
  void SetupBuffers();
  void DebugPrint();
  void Render(glm::mat4 model_transform);
protected:
  GLuint vertex_array_id_;
  GLuint vertex_buffer_position_id_;
  GLuint shader_id_;
  GLuint mvp_id_;
  glm::vec3 scale_;
  std::vector<glm::vec3> vertex_data_;
};


#endif // SHAPE_H