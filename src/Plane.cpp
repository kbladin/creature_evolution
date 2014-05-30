#include "Plane.h"

//! Constructor. All vertex data are set up.
/*!
  The default Plane has a horisontal normal and is of size 1.
  Currently, the texture type is set in this constructor and can therefore
  not be different for different planes.
*/
Plane::Plane(Material material) : Shape(material) {
  SetupVertexPositionData();
  SetupVertexNormalData();
  SetupVertexUVData();
  SetupElementData();
  TextureManager::Instance();
}

//! Constructor. All vertex data are set up.
/*!
  Currently, the texture type is set in this constructor and can therefore
  not be different for different planes.
  \param scale scales the plane in all 3 dimensions.
*/
Plane::Plane(glm::vec3 scale, Material material) : Shape(material) {
  SetupVertexPositionData();
  SetupVertexNormalData();
  SetupVertexUVData();
  SetupElementData();
  for (int i = 0; i < vertex_position_data_.size(); ++i) {
    vertex_position_data_[i].x = vertex_position_data_[i].x*scale.x;
    vertex_position_data_[i].y = vertex_position_data_[i].y*scale.y;
    vertex_position_data_[i].z = vertex_position_data_[i].z*scale.z;
  }
}

//! Constructor. All vertex data are set up.
/*!
  Currently, the texture type is set in this constructor and can therefore
  not be different for different planes.
  \param scale scales the plane in all 3 dimensions.
  \param plane_equation defines a normal and a position along it. Currently
  only the translation is implemented.
*/
Plane::Plane(glm::vec3 scale, glm::vec4 plane_equation, Material material) :
        Shape(material) {
  SetupVertexPositionData();
  SetupVertexNormalData();
  SetupVertexUVData();
  SetupElementData();
  for (int i = 0; i < vertex_position_data_.size(); ++i) {
    vertex_position_data_[i].x = vertex_position_data_[i].x*scale.x;
    vertex_position_data_[i].y = vertex_position_data_[i].y*scale.y;
    vertex_position_data_[i].z = vertex_position_data_[i].z*scale.z;
  }
  //translate plane
  for(int i=0; i < vertex_position_data_.size(); ++i) {
      vertex_position_data_[i].y = plane_equation.w;
  }
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
