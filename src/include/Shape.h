#ifndef SHAPE_H
#define SHAPE_H

// C++
#include <vector>
#include <iostream>
// External
#include <GL/glew.h>
#ifndef Q_MOC_RUN
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#endif
// Internal
#include "Camera.h"
#include "ShaderManager.h"
#include "TextureManager.h"

//class Camera;

class Shape {
public:
  Shape();
  void SetupBuffers();
  void DebugPrint();
  void Render(Camera camera, glm::mat4 model_transform);
protected:
  GLuint vertex_array_id_;
  GLuint element_buffer_id_;
  GLuint vertex_position_buffer_id_;
  GLuint vertex_normal_buffer_id_;
  GLuint vertex_uv_buffer_id_;

  std::vector<glm::vec3> vertex_position_data_;
  std::vector<glm::vec3> vertex_normal_data_;
  std::vector<glm::vec2> vertex_uv_data_;
  std::vector<GLushort> element_data_;

  Material material_;
};

#endif // SHAPE_H
