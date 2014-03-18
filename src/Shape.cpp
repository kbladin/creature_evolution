#include <Shape.h>

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