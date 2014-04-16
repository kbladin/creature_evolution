#include "Plane.h"

Plane::Plane() {
  SetupVertexPositionData();
  SetupVertexNormalData();
  SetupVertexUVData();
  SetupElementData();
  TextureManager::Instance();
  material_.texture_type = TextureType::CHECKERBOARD;
}

Plane::Plane(glm::vec3 scale) {
  SetupVertexPositionData();
  SetupVertexNormalData();
  SetupVertexUVData();
  SetupElementData();
  for (int i = 0; i < vertex_position_data_.size(); ++i) {
    vertex_position_data_[i].x = vertex_position_data_[i].x*scale.x;
    vertex_position_data_[i].y = vertex_position_data_[i].y*scale.y;
    vertex_position_data_[i].z = vertex_position_data_[i].z*scale.z;
  }
  material_.texture_type = TextureType::CHECKERBOARD;
}

void Plane::SetupVertexPositionData() {
  vertex_position_data_.resize(8);

  vertex_position_data_[0] = glm::vec3(-1.0f, 0.0f, -1.0f);
  vertex_position_data_[1] = glm::vec3(1.0f, 0.0f, -1.0f);
  vertex_position_data_[2] = glm::vec3(-1.0f, 0.0f, 1.0f);
  vertex_position_data_[3] = glm::vec3(1.0f, 0.0f, 1.0f);

  vertex_position_data_[4] = glm::vec3(-1.0f, 0.0f, -1.0f);
  vertex_position_data_[5] = glm::vec3(1.0f, 0.0f, -1.0f);
  vertex_position_data_[6] = glm::vec3(-1.0f, 0.0f, 1.0f);
  vertex_position_data_[7] = glm::vec3(1.0f, 0.0f, 1.0f);
}

void Plane::SetupVertexNormalData() {
  vertex_normal_data_.resize(8);

  vertex_normal_data_[0] = glm::vec3(0.0f, 1.0f, 0.0f);
  vertex_normal_data_[1] = glm::vec3(0.0f, 1.0f, 0.0f);
  vertex_normal_data_[2] = glm::vec3(0.0f, 1.0f, 0.0f);
  vertex_normal_data_[3] = glm::vec3(0.0f, 1.0f, 0.0f);

  vertex_normal_data_[4] = glm::vec3(0.0f, -1.0f, 0.0f);
  vertex_normal_data_[5] = glm::vec3(0.0f, -1.0f, 0.0f);
  vertex_normal_data_[6] = glm::vec3(0.0f, -1.0f, 0.0f);
  vertex_normal_data_[7] = glm::vec3(0.0f, -1.0f, 0.0f);
}

void Plane::SetupVertexUVData() {
  vertex_uv_data_.resize(8);

  vertex_uv_data_[0] = glm::vec2(0.0f, 1.0f);
  vertex_uv_data_[1] = glm::vec2(1.0f, 1.0f);
  vertex_uv_data_[2] = glm::vec2(0.0f, 0.0f);
  vertex_uv_data_[3] = glm::vec2(1.0f, 0.0f);

  vertex_uv_data_[4] = glm::vec2(1.0f, 1.0f);
  vertex_uv_data_[5] = glm::vec2(0.0f, 1.0f);
  vertex_uv_data_[6] = glm::vec2(1.0f, 0.0f);
  vertex_uv_data_[7] = glm::vec2(0.0f, 0.0f);
}

void Plane::SetupElementData() {
  element_data_.resize(12);

  element_data_[0] = 0;
  element_data_[1] = 2;
  element_data_[2] = 1;

  element_data_[3] = 1;
  element_data_[4] = 2;
  element_data_[5] = 3;

  element_data_[6] = 4;
  element_data_[7] = 5;
  element_data_[8] = 6;

  element_data_[9] = 5;
  element_data_[10] = 6;
  element_data_[11] = 7;
}
