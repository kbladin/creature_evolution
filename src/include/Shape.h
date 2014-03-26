#ifndef SHAPE_H
#define SHAPE_H

// C++
#include <vector>
#include <iostream>
// External
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
// Internal
#include "Camera.h"
#include "ShaderManager.h"


class Shape {
public:
	Shape() { };
  void SetupBuffers();
  void DebugPrint();
  void Render(Camera camera, glm::mat4 model_transform);
protected:
  GLuint vertex_array_id_;
  GLuint vertex_buffer_position_id_;
  GLuint shader_id_;
  GLuint mvp_id_;
  std::vector<glm::vec3> vertex_data_;
};


#endif // SHAPE_H
