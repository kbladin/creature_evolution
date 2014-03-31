#include "Plane.h"

Plane::Plane() {
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,0.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,0.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,0.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,-1.0f));
}

Plane::Plane(glm::vec3 scale) {
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,0.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,0.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,0.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,0.0f,-1.0f));

	for(int i = 0; i < vertex_data_.size(); ++i) {
		vertex_data_[i].x = vertex_data_[i].x*scale.x;
		vertex_data_[i].y = vertex_data_[i].y*scale.y;
		vertex_data_[i].z = vertex_data_[i].z*scale.z;
	}
}