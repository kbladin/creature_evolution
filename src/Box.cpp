#include "Box.h"

Box::Box() {
	/*	Setting up vertex data
		This will setup a 6-sided unit cube
	*/
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f, 1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f, 1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,-1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f, 1.0f));

	vertex_data_.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));	//8
	vertex_data_.push_back(glm::vec3(1.0f,1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,1.0f));


}

Box::Box(float scale_x, float scale_y, float scale_z) {
	/*	Setting up vertex data
		This will setup a 6-sided unit cube
	*/
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f, 1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f, 1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,-1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,-1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f, 1.0f));

	vertex_data_.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));	//8
	vertex_data_.push_back(glm::vec3(1.0f,1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,-1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,-1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,1.0f));

	vertex_data_.push_back(glm::vec3(1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(-1.0f,1.0f,1.0f));
	vertex_data_.push_back(glm::vec3(1.0f,-1.0f,1.0f));

	for(int i = 0; i < vertex_data_.size(); ++i)
	{
		vertex_data_[i].x = vertex_data_[i].x*scale_x;
		vertex_data_[i].y = vertex_data_[i].y*scale_y;
		vertex_data_[i].z = vertex_data_[i].z*scale_z;
	}

}


