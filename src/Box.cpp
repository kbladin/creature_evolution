#include "Box.h"

Box::Box() {
  SetupVertexPositionData();
  SetupVertexNormalData();
  SetupVertexUVData();
  SetupElementData();
}

Box::Box(float scale_x, float scale_y, float scale_z) {
  SetupVertexPositionData();
  SetupVertexNormalData();
  SetupVertexUVData();
  SetupElementData();
  for (int i = 0; i < vertex_position_data_.size(); ++i) {
    vertex_position_data_[i].x = vertex_position_data_[i].x*scale_x;
    vertex_position_data_[i].y = vertex_position_data_[i].y*scale_y;
    vertex_position_data_[i].z = vertex_position_data_[i].z*scale_z;
  }
}

void Box::SetupVertexPositionData() {
  vertex_position_data_.resize(24);

  vertex_position_data_[0] = glm::vec3(-1.0f, -1.0f, -1.0f);
  vertex_position_data_[1] = glm::vec3(1.0f, -1.0f, -1.0f);
  vertex_position_data_[2] = glm::vec3(-1.0f, 1.0f, -1.0f);
  vertex_position_data_[3] = glm::vec3(1.0f, 1.0f, -1.0f);

  vertex_position_data_[4] = glm::vec3(-1.0f, -1.0f, 1.0f);
  vertex_position_data_[5] = glm::vec3(1.0f, -1.0f, 1.0f);
  vertex_position_data_[6] = glm::vec3(-1.0f, 1.0f, 1.0f);
  vertex_position_data_[7] = glm::vec3(1.0f, 1.0f, 1.0f);

  vertex_position_data_[8] = glm::vec3(-1.0f, -1.0f, -1.0f);
  vertex_position_data_[9] = glm::vec3(-1.0f, -1.0f, 1.0f);
  vertex_position_data_[10] = glm::vec3(-1.0f, 1.0f, -1.0f);
  vertex_position_data_[11] = glm::vec3(-1.0f, 1.0f, 1.0f);

  vertex_position_data_[12] = glm::vec3(1.0f, -1.0f, -1.0f);
  vertex_position_data_[13] = glm::vec3(1.0f, -1.0f, 1.0f);
  vertex_position_data_[14] = glm::vec3(1.0f, 1.0f, -1.0f);
  vertex_position_data_[15] = glm::vec3(1.0f, 1.0f, 1.0f);

  vertex_position_data_[16] = glm::vec3(-1.0f, -1.0f, -1.0f);
  vertex_position_data_[17] = glm::vec3(1.0f, -1.0f, -1.0f);
  vertex_position_data_[18] = glm::vec3(-1.0f, -1.0f, 1.0f);
  vertex_position_data_[19] = glm::vec3(1.0f, -1.0f, 1.0f);

  vertex_position_data_[20] = glm::vec3(-1.0f, 1.0f, -1.0f);
  vertex_position_data_[21] = glm::vec3(1.0f, 1.0f, -1.0f);
  vertex_position_data_[22] = glm::vec3(-1.0f, 1.0f, 1.0f);
  vertex_position_data_[23] = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Box::SetupVertexNormalData() {
  vertex_normal_data_.resize(24);

  vertex_normal_data_[0] = glm::vec3(0.0f, 0.0f, -1.0f);
  vertex_normal_data_[1] = glm::vec3(0.0f, 0.0f, -1.0f);
  vertex_normal_data_[2] = glm::vec3(0.0f, 0.0f, -1.0f);
  vertex_normal_data_[3] = glm::vec3(0.0f, 0.0f, -1.0f);

  vertex_normal_data_[4] = glm::vec3(0.0f, 0.0f, 1.0f);
  vertex_normal_data_[5] = glm::vec3(0.0f, 0.0f, 1.0f);
  vertex_normal_data_[6] = glm::vec3(0.0f, 0.0f, 1.0f);
  vertex_normal_data_[7] = glm::vec3(0.0f, 0.0f, 1.0f);

  vertex_normal_data_[8] = glm::vec3(-1.0f, 0.0f, 0.0f);
  vertex_normal_data_[9] = glm::vec3(-1.0f, 0.0f, 0.0f);
  vertex_normal_data_[10] = glm::vec3(-1.0f, 0.0f, 0.0f);
  vertex_normal_data_[11] = glm::vec3(-1.0f, 0.0f, 0.0f);

  vertex_normal_data_[12] = glm::vec3(1.0f, 0.0f, 0.0f);
  vertex_normal_data_[13] = glm::vec3(1.0f, 0.0f, 0.0f);
  vertex_normal_data_[14] = glm::vec3(1.0f, 0.0f, 0.0f);
  vertex_normal_data_[15] = glm::vec3(1.0f, 0.0f, 0.0f);

  vertex_normal_data_[16] = glm::vec3(0.0f, -1.0f, 0.0f);
  vertex_normal_data_[17] = glm::vec3(0.0f, -1.0f, 0.0f);
  vertex_normal_data_[18] = glm::vec3(0.0f, -1.0f, 0.0f);
  vertex_normal_data_[19] = glm::vec3(0.0f, -1.0f, 0.0f);

  vertex_normal_data_[20] = glm::vec3(0.0f, 1.0f, 0.0f);
  vertex_normal_data_[21] = glm::vec3(0.0f, 1.0f, 0.0f);
  vertex_normal_data_[22] = glm::vec3(0.0f, 1.0f, 0.0f);
  vertex_normal_data_[23] = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Box::SetupVertexUVData() {
  vertex_uv_data_.resize(24);

  vertex_uv_data_[0] = glm::vec2(1.0f, 1.0f);
  vertex_uv_data_[1] = glm::vec2(1.0f, 2/3.0f);
  vertex_uv_data_[2] = glm::vec2(2/3.0f, 1.0f);
  vertex_uv_data_[3] = glm::vec2(2/3.0f, 2/3.0f);

  vertex_uv_data_[4] = glm::vec2(0.0f, 1.0f);
  vertex_uv_data_[5] = glm::vec2(0.0f, 2/3.0f);
  vertex_uv_data_[6] = glm::vec2(1/3.0f, 1.0f);
  vertex_uv_data_[7] = glm::vec2(1/3.0f, 2/3.0f);

  vertex_uv_data_[8] = glm::vec2(1/3.0f, 1/3.0f);
  vertex_uv_data_[9] = glm::vec2(1/3.0f, 2/3.0f);
  vertex_uv_data_[10] = glm::vec2(0.0f, 1/3.0f);
  vertex_uv_data_[11] = glm::vec2(0.0f, 2/3.0f);

  vertex_uv_data_[12] = glm::vec2(2/3.0f, 1/3.0f);
  vertex_uv_data_[13] = glm::vec2(2/3.0f, 2/3.0f);
  vertex_uv_data_[14] = glm::vec2(1.0f, 1/3.0f);
  vertex_uv_data_[15] = glm::vec2(1.0f, 2/3.0f);

  vertex_uv_data_[16] = glm::vec2(1/3.0f, 1/3.0f);
  vertex_uv_data_[17] = glm::vec2(2/3.0f, 1/3.0f);
  vertex_uv_data_[18] = glm::vec2(1/3.0f, 2/3.0f);
  vertex_uv_data_[19] = glm::vec2(2/3.0f, 2/3.0f);

  vertex_uv_data_[20] = glm::vec2(2/3.0f, 1.0f);
  vertex_uv_data_[21] = glm::vec2(2/3.0f, 2/3.0f);
  vertex_uv_data_[22] = glm::vec2(1/3.0f, 1.0f);
  vertex_uv_data_[23] = glm::vec2(1/3.0f, 2/3.0f);
}

void Box::SetupElementData() {
  element_data_.resize(36);

  element_data_[0] = 0;
  element_data_[1] = 3;
  element_data_[2] = 1;

  element_data_[3] = 0;
  element_data_[4] = 2;
  element_data_[5] = 3;

  element_data_[6] = 4;
  element_data_[7] = 5;
  element_data_[8] = 7;

  element_data_[9] = 4;
  element_data_[10] = 7;
  element_data_[11] = 6;

  element_data_[12] = 9;
  element_data_[13] = 11;
  element_data_[14] = 8;

  element_data_[15] = 8;
  element_data_[16] = 11;
  element_data_[17] = 10;

  element_data_[18] = 12;
  element_data_[19] = 15;
  element_data_[20] = 13;

  element_data_[21] = 12;
  element_data_[22] = 14;
  element_data_[23] = 15;

  element_data_[24] = 17;
  element_data_[25] = 18;
  element_data_[26] = 16;

  element_data_[27] = 17;
  element_data_[28] = 19;
  element_data_[29] = 18;

  element_data_[30] = 20;
  element_data_[31] = 22;
  element_data_[32] = 21;

  element_data_[33] = 21;
  element_data_[34] = 22;
  element_data_[35] = 23;
}
