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
  // Matrix data
  glm::mat4 V = camera.GetViewMatrix();
  glm::mat4 MV = V * model_transform;
	glm::mat4 P = camera.GetProjectionMatrix();
  glm::mat4 MVP = P * MV;
  
  // To make sure we use the same name
  const char* shader_name = "Basic";
  ShaderManager::Instance()->UseProgram(shader_name);
  ShaderManager::Instance()->GetShaderProgramFromName(shader_name)->UniformMatrix4fv("MVP", 1, false, &MVP[0][0]);
  ShaderManager::Instance()->GetShaderProgramFromName(shader_name)->UniformMatrix4fv("M", 1, false, &model_transform[0][0]);
  ShaderManager::Instance()->GetShaderProgramFromName(shader_name)->UniformMatrix4fv("V", 1, false, &V[0][0]);
  ShaderManager::Instance()->GetShaderProgramFromName(shader_name)->UniformMatrix4fv("MV", 1, false, &MV[0][0]);
  
	glBindVertexArray(vertex_array_id_);
	glDrawArrays(GL_TRIANGLES, 0, vertex_data_.size());
  glBindVertexArray(0);

	glUseProgram(0);
}
