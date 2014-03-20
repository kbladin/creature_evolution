#include "Plane.h"

Plane::Plane() {
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,0.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,0.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,0.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,-1.0f));

}