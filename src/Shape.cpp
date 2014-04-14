#include "Shape.h"

Shape::Shape() {
    vertex_array_id_ = GL_FALSE;
    element_buffer_id_ = GL_FALSE;
    vertex_position_buffer_id_ = GL_FALSE;
    vertex_normal_buffer_id_ = GL_FALSE;
    vertex_uv_buffer_id_ = GL_FALSE;
}

void Shape::DebugPrint() {
  for (int i = 0; i < vertex_position_data_.size(); ++i) {
    std::cout << glm::to_string(vertex_position_data_[i]) << std::endl;
  }
}

void Shape::SetupBuffers() {
  // Generate the vertex array
  glGenVertexArrays(1, &vertex_array_id_);
  glBindVertexArray(vertex_array_id_);

  // Generate the element buffer
  glGenBuffers(1, &element_buffer_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id_);
  glBufferData(
          GL_ELEMENT_ARRAY_BUFFER,
          sizeof(GLushort) * element_data_.size(),
          &element_data_[0],
          GL_STATIC_DRAW);

  // Generate the vertex position buffer
  glGenBuffers(1, &vertex_position_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_position_buffer_id_);
  glBufferData(
          GL_ARRAY_BUFFER,
          sizeof(glm::vec3) * vertex_position_data_.size(),
          &vertex_position_data_[0],
          GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
          0,                  // attribute, same as in shader.
          3,                  // size
          GL_FLOAT,           // type
          GL_FALSE,           // normalized?
          0,                  // stride
          reinterpret_cast<void*>(0));  // array buffer offset

  // Generate the vertex normal buffer
  glGenBuffers(1, &vertex_normal_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_normal_buffer_id_);
  glBufferData(
          GL_ARRAY_BUFFER,
          sizeof(glm::vec3) * vertex_normal_data_.size(),
          &vertex_normal_data_[0],
          GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(
          1,                  // attribute, same as in shader.
          3,                  // size
          GL_FLOAT,           // type
          GL_FALSE,           // normalized?
          0,                  // stride
          reinterpret_cast<void*>(0));  // array buffer offset

  // Generate the vertex UV buffer
  glGenBuffers(1, &vertex_uv_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_uv_buffer_id_);
  glBufferData(
          GL_ARRAY_BUFFER,
          sizeof(glm::vec2) * vertex_uv_data_.size(),
          &vertex_uv_data_[0],
          GL_STATIC_DRAW);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(
          2,                  // attribute, same as in shader.
          2,                  // size
          GL_FLOAT,           // type
          GL_FALSE,           // normalized?
          0,                  // stride
          reinterpret_cast<void*>(0));  // array buffer offset

  // Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Shape::Render(Camera camera, glm::mat4 model_transform) {
  // Matrix data
  glm::mat4 V = camera.GetViewMatrix();
  glm::mat4 MV = V * model_transform;
  glm::mat4 P = camera.GetProjectionMatrix();
  glm::mat4 MVP = P * MV;

  // To make sure we use the same name
  const char* shader_name = "Basic";
  ShaderManager::Instance()->UseProgram(shader_name);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->UniformMatrix4fv("MVP", 1, false, &MVP[0][0]);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->UniformMatrix4fv("M", 1, false, &model_transform[0][0]);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->UniformMatrix4fv("V", 1, false, &V[0][0]);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->UniformMatrix4fv("MV", 1, false, &MV[0][0]);
  ShaderManager::Instance()->GetShaderProgramFromName(
          shader_name)->Uniform1f("far_clipping", camera.GetFarClipping());

  glBindVertexArray(vertex_array_id_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_id_);

  glDrawElements(
          GL_TRIANGLES,      // mode
          element_data_.size(),    // count
          GL_UNSIGNED_SHORT,   // type
          reinterpret_cast<void*>(0));  // element array buffer offset

  // Unbind
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glUseProgram(0);
}
