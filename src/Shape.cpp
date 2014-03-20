#include <GL/glew.h>
#include <Shape.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <Shader.hpp>

void Shape::DebugPrint() {
	for(int i = 0; i < vertex_data_.size(); ++i) {
		std::cout << glm::to_string(vertex_data_[i]) << std::endl;
	}
}

void Shape::SetupBuffers() {
	
	shader_id_ = LoadShaders( "mvp.vert",
		"simple.frag" );
	mvp_id_ = glGetUniformLocation(shader_id_, "MVP");
	
	glGenVertexArrays(1, &vertex_array_id_);
	glBindVertexArray(vertex_array_id_);

	glGenBuffers(1, &vertex_buffer_position_id_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_position_id_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*3* vertex_data_.size(), 
			&vertex_data_[0], GL_STATIC_DRAW);
}

void Shape::Render(glm::mat4 model_transform) {
	//std::cout << "Rendering shape.." << std::endl;
	glUseProgram(shader_id_);
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View       = glm::lookAt(
								glm::vec3(0,3,-5), // Camera is at (4,3,-3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	glm::mat4 rotate_view = glm::rotate(90.0f, glm::vec3(0,1,0));
	//glm::mat4 Model      = glm::mat4(1.0f);
	glm::mat4 MVP        = Projection * View * rotate_view * model_transform; // Remember, matrix multiplication is the other way around

	glUniformMatrix4fv(mvp_id_, 1, GL_FALSE, &MVP[0][0]);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_position_id_);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	glDrawArrays(GL_TRIANGLES, 0, vertex_data_.size()); // 12*3 indices starting at 0 -> 12 triangles


	glDisableVertexAttribArray(0);
	glUseProgram(0);

}