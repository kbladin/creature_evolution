#include "Shape.h"

void Shape::DebugPrint() {
	for(int i = 0; i < vertex_data_.size(); ++i) {
		std::cout << glm::to_string(vertex_data_[i]) << std::endl;
	}
}

void Shape::SetupBuffers() {
	glGenVertexArrays(1, &vertex_array_id_);
	glBindVertexArray(vertex_array_id_);

	glGenBuffers(1, &vertex_buffer_position_id_);
    glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_position_id_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*3* vertex_data_.size(), 
			&vertex_data_[0], GL_STATIC_DRAW);
	glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Shape::Render(Camera camera, glm::mat4 model_transform) {
	//std::cout << "Rendering shape.." << std::endl;
  
  const char* shader_name = "Simple_MVP";
  
	glUseProgram(ShaderManager::Instance()->GetShaderFromName(shader_name)->getID());
  
	glm::mat4 Projection = camera.GetProjectionMatrix();
	glm::mat4 View       = camera.GetViewMatrix();
	glm::mat4 rotate_view = glm::rotate(90.0f, glm::vec3(0,1,0));
	glm::mat4 MVP        = Projection * View * rotate_view * model_transform;

  // Upload data to the GPU
	glUniformMatrix4fv(ShaderManager::Instance()->GetShaderFromName(shader_name)->mvp_loc_, 1, GL_FALSE, &MVP[0][0]);
  
	glBindVertexArray(vertex_array_id_);
	glDrawArrays(GL_TRIANGLES, 0, vertex_data_.size());
  glBindVertexArray(0);

	glUseProgram(0);
}