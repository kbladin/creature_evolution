#include "ShaderManager.h"

///////////////////
// ShaderManager //
///////////////////

ShaderManager* ShaderManager::instance_ = NULL;

//! A part of the singleton pattern
/*!
 If this function is called for the first time, the constructor is called and the singleton is created.
 \return The one instance of the ShaderManager
 */
ShaderManager* ShaderManager::Instance() {
	if (!instance_) // only allow one instance of class to be generated
		instance_ = new ShaderManager();
	return instance_;
}

//! ShaderManager constructor.
/*!
 First all shaders are added and compiled by calling the function AddAllShaders(). Then all the individual shader programs are linked. These use the shaders added in the previous call.
*/

ShaderManager::ShaderManager(){
  AddAllShaders();
  AddSimpleMvpShaderProgram();
  AddBasicShaderProgram();
}

//! ShaderManager destructor
/*!
 First, all shaders are deleted, then all shader programs.
*/

ShaderManager::~ShaderManager(){
  //Delete shaders
  std::map<std::string, Shader*>::iterator shader_iter = shaders_.begin();
  while (shader_iter != shaders_.end()) {
    delete shader_iter->second;
    shader_iter++;
  }
  //Delete shader programs
  std::map<std::string, ShaderProgram*>::iterator shader_program_iter = shader_programs_.begin();
  while (shader_program_iter != shader_programs_.end()) {
    delete shader_program_iter->second;
    shader_program_iter++;
  }
}

//! Add all shaders specified
/*!
 All the shaders used by the program shall be added. First all shaders are created (compiled) and then they are put in the std::map of shaders.
*/

void ShaderManager::AddAllShaders(){
  // Create shaders
  Shader* simple_mvp_vert = new Shader("data/shaders/mvp.vert",GL_VERTEX_SHADER);
  Shader* simple_mvp_frag = new Shader("data/shaders/simple.frag",GL_FRAGMENT_SHADER);
  Shader* basic_vert = new Shader("data/shaders/basic.vert",GL_VERTEX_SHADER);
  Shader* basic_frag = new Shader("data/shaders/basic.frag",GL_FRAGMENT_SHADER);
  // Put shaders in the map
  shaders_.insert(StringShaderPair("Simple_MVP_Vert", simple_mvp_vert));
  shaders_.insert(StringShaderPair("Simple_MVP_Frag", simple_mvp_frag));
  shaders_.insert(StringShaderPair("Basic_Vert", basic_vert));
  shaders_.insert(StringShaderPair("Basic_Frag", basic_frag));
}

//! Add the specific shader program Simple_MVP
/*!
 This is a specific creator function for the shader Simple_MVP. This function relies on that the specific shaders used are already compiled. Therefore they can be picked from the std::map of shaders and then put in the constructor of the new shader program. The shader program is then inserted in the shader manager. All the specific locations also needs to be added, these are then called by name instead of GLuint.
*/

void ShaderManager::AddSimpleMvpShaderProgram(){
  // Create shader program
  ShaderProgram* simple_mvp_shader_program =
    new ShaderProgram(shaders_["Simple_MVP_Vert"],
                      shaders_["Simple_MVP_Frag"]);
  // The name with which to refer to the shader program
  const char* shader_program_name = "Simple_MVP";
  // Put shader program in the map
  shader_programs_.insert(StringShaderProgPair(shader_program_name, simple_mvp_shader_program) );
  // Create all locations
  shader_programs_[shader_program_name]->CreateUniformLocation("MVP");
}

//! Add the specific shader program Basic
/*!
 This is a specific creator function for the shader Basic. This function relies on that the specific shaders used are already compiled. Therefore they can be picked from the std::map of shaders and then put in the constructor of the new shader program. The shader program is then inserted in the shader manager. All the specific locations also needs to be added, these are then called by name instead of GLuint.
 */

void ShaderManager::AddBasicShaderProgram(){
  // Create shader program
  ShaderProgram* simple_mvp_shader_program =
  new ShaderProgram(shaders_["Basic_Vert"],
                    shaders_["Basic_Frag"]);
  // The name with which to refer to the shader program
  const char* shader_program_name = "Basic";
  // Put shader program in the map
  shader_programs_.insert(StringShaderProgPair(shader_program_name, simple_mvp_shader_program) );
  // Create all locations
  shader_programs_[shader_program_name]->CreateUniformLocation("MVP");
  shader_programs_[shader_program_name]->CreateUniformLocation("MV");
  shader_programs_[shader_program_name]->CreateUniformLocation("M");
  shader_programs_[shader_program_name]->CreateUniformLocation("V");
}

//! Used for accessing the shader programs.
/*!
 Instead of relying on GLints, names are used for getting shader programs.
\param The name key of the wanted shader program
\return A pointer to the corresponding shader program
*/

ShaderProgram* ShaderManager::GetShaderProgramFromName(const char* name){
  return shader_programs_[name];
}

//! Used for binding shader programs.
/*!
 Bind the shader program specified by the name key. If the shader program is not found, the default shader program is bound.
 \param The name key of the shader program to bind.
 */

void ShaderManager::UseProgram(const char* name){
  glUseProgram(shader_programs_[name]->getID());
}

//! Used for unbinding shader programs.
/*!
 Unbind the current shader program. The same as binding the default shade program (0)
*/

void ShaderManager::UnbindCurrentShader(){
  glUseProgram(0);
}

///////////////////
// ShaderProgram //
///////////////////

//! Constructor for the ShaderProgram class
/*!
 All the shaders passed in the arguments gets linked in to a shader program.
 \param Pointers to the shaders to be linked in the order vertex, fragment, geometry and tesselation shader. Vertex and fragment shaders are the only ones that are needed.
 */

ShaderProgram::ShaderProgram(Shader* vertex_shader,
                             Shader* fragment_shader,
                             Shader* geometry_shader,
                             Shader* tesselation_shader){
  if(vertex_shader == NULL || fragment_shader == NULL){
    program_id_ = 0;
    std::cout << "ERROR: Shader program could not be created. Vertex shader and fragment shader are required!" << std::endl;
    return;
  }
  
  // Link the program
	printf("Linking Shader program\n");
	program_id_ = glCreateProgram();
  
  GLint result = GL_FALSE;
	int info_log_length;
	
  if (vertex_shader) {
    glAttachShader(program_id_, vertex_shader->GetShaderId());
  }
  if (fragment_shader) {
    glAttachShader(program_id_, fragment_shader->GetShaderId());
  }
  if (geometry_shader) {
    glAttachShader(program_id_, geometry_shader->GetShaderId());
  }
  if (tesselation_shader) {
    glAttachShader(program_id_, tesselation_shader->GetShaderId());
  }
  glLinkProgram(program_id_);
  
	// Check the program
	glGetProgramiv(program_id_, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &info_log_length);
	if ( info_log_length > 0 ){
		std::vector<char> program_error_message(info_log_length+1);
		glGetProgramInfoLog(program_id_, info_log_length, NULL, &program_error_message[0]);
		printf("%s\n", &program_error_message[0]);
    
    program_id_ = 0;
    return;
	}
}

//! Delete the shader program.

ShaderProgram::~ShaderProgram(){
  glDeleteProgram(program_id_);
}

//! Create a location for an attribute in the shader program.
/*!
 The name of the attribute needs to be specified in the source code of the shader. If it is not found it can not be created and an error message is printed. If it is found, the location is added to the std::map of attributes. Then they can be accessed via name instead of GLint.
 \param The name of the attribute for which to create the location.
*/

void ShaderProgram::CreateAttribLocation(const char* name){
  GLint loc = glGetAttribLocation(program_id_, name);
  if (loc == -1) {
    std::cout << "Error: Unknown Attrib name: " << name <<
    ". Could not create Attrib location." << std::endl;
  } else{
    attribute_locations_.insert(std::pair<std::string, GLint>(name,loc));
  }
}

//! Create a location for a uniform in the shader program.
/*!
 The name of the uniform needs to be specified in the source code of the shader. If it is not found it can not be created and an error message is printed. If it is found, the location is added to the std::map of uniforms. Then they can be accessed via name instead of GLint.
 \param The name of the uniform for which to create the location.
 */

void ShaderProgram::CreateUniformLocation(const char* name){
  GLint loc = glGetUniformLocation(program_id_, name);
  if (loc == -1) {
    std::cout << "Error: Unknown Uniform name: " << name <<
    ". Could not create Uniform location." << std::endl;
        uniform_locations_.insert(std::pair<std::string, GLint>(name,loc));
  } else{
    uniform_locations_.insert(std::pair<std::string, GLint>(name,loc));
  }
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
*/

// Uniforms
void ShaderProgram::Uniform1f(const char* name, GLfloat v0){
  glUniform1f(uniform_locations_[name], v0);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
 \param value
*/

void ShaderProgram::Uniform2f(const char* name, GLfloat v0, GLfloat v1){
  glUniform2f(uniform_locations_[name], v0, v1);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
 \param value
 \param value
*/

void ShaderProgram::Uniform3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2){
  glUniform3f(uniform_locations_[name], v0, v1, v2);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
 \param value
 \param value
*/

void ShaderProgram::Uniform4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
  glUniform4f(uniform_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
*/

void ShaderProgram::Uniform1i(const char* name, GLint v0){
  glUniform1i(uniform_locations_[name], v0);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
 \param value
 */

void ShaderProgram::Uniform2i(const char* name, GLint v0, GLint v1){
  glUniform2i(uniform_locations_[name], v0, v1);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
 \param value
 \param value
 */

void ShaderProgram::Uniform3i(const char* name, GLint v0, GLint v1, GLint v2){
  glUniform3i(uniform_locations_[name], v0, v1, v2);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
 \param value
 \param value
 */

void ShaderProgram::Uniform4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3){
  glUniform4i(uniform_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param value
 */

void ShaderProgram::Uniform1fv(const char* name, GLsizei count, const GLfloat *value){
  glUniform1fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param count
 \param value
 */

void ShaderProgram::Uniform2fv(const char* name, GLsizei count, const GLfloat *value){
  glUniform2fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param value
 */

void ShaderProgram::Uniform3fv(const char* name, GLsizei count, const GLfloat *value){
  glUniform3fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param value
 */

void ShaderProgram::Uniform4fv(const char* name, GLsizei count, const GLfloat *value){
  glUniform4fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param value
 */

void ShaderProgram::Uniform1iv(const char* name, GLsizei count, const GLint *value){
  glUniform1iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param value
 */

void ShaderProgram::Uniform2iv(const char* name, GLsizei count, const GLint *value){
  glUniform2iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param value
 */

void ShaderProgram::Uniform3iv(const char* name, GLsizei count, const GLint *value){
  glUniform3iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param value
 */

void ShaderProgram::Uniform4iv(const char* name, GLsizei count, const GLint *value){
  glUniform4iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param transpose
 \param value
 */

void ShaderProgram::UniformMatrix2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value){
  glUniformMatrix2fv(uniform_locations_[name], count, transpose, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param transpose
 \param value
 */

void ShaderProgram::UniformMatrix3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value){
  glUniformMatrix3fv(uniform_locations_[name], count, transpose, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param Name key of the uniform
 \param count
 \param transpose
 \param value
 */

void ShaderProgram::UniformMatrix4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value){
  glUniformMatrix4fv(uniform_locations_[name], count, transpose, value);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the uniform
 \param value
 */

// Attributes
void ShaderProgram::VertexAttrib1f(const char* name, GLfloat v0){
  glVertexAttrib1f(attribute_locations_[name], v0);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 \param value
 */

void ShaderProgram::VertexAttrib2f(const char* name, GLfloat v0, GLfloat v1){
  glVertexAttrib2f(attribute_locations_[name], v0, v1);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 \param value
 \param value
 */

void ShaderProgram::VertexAttrib3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2){
  glVertexAttrib3f(attribute_locations_[name], v0, v1, v2);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 \param value
 \param value
 \param value
 */

void ShaderProgram::VertexAttrib4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
  glVertexAttrib4f(attribute_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 \param value
 \param value
 \param value
 */

void ShaderProgram::VertexAttribI4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3){
  glVertexAttribI4i(attribute_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 \param value
 \param value
 \param value
 */

void ShaderProgram::VertexAttribI4ui(const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3){
  glVertexAttribI4ui(attribute_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
*/

void ShaderProgram::VertexAttrib1fv(const char* name, const GLfloat *v){
  glVertexAttrib1fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 */

void ShaderProgram::VertexAttrib2fv(const char* name, const GLfloat *v){
  glVertexAttrib2fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 */

void ShaderProgram::VertexAttrib3fv(const char* name, const GLfloat *v){
  glVertexAttrib3fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 */

void ShaderProgram::VertexAttrib4fv(const char* name, const GLfloat *v){
  glVertexAttrib4fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 */

void ShaderProgram::VertexAttribI4iv(const char* name, const GLint *v){
  glVertexAttribI4iv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param Name key of the attribute
 \param value
 */

void ShaderProgram::VertexAttribI4uiv(const char* name, const GLuint *v){
  glVertexAttribI4uiv(attribute_locations_[name], v);
}

//! Get the id for the shader program
/*!
 \return The id for the program
*/

GLuint ShaderProgram::getID(){
  return program_id_;
}

////////////
// Shader //
////////////

//! Constructor for the shader
/*!
 Compiles the shader from the file path.
 \param File path for where the shader source is to be found.
 \param Type of the shader. Can be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
 */

Shader::Shader(const char* file_path, int type){
  // Create the shader
  shader_id_ = glCreateShader(type);
  if (shader_id_ == 0) {
    std::cout << "ERROR: Invalid shader type: " << type << "!" << std::endl;
    return;
  }
  // Read the Shader code from the file
	std::string shader_code;
	std::ifstream shader_stream(file_path, std::ios::in);
	if(shader_stream.is_open()){
		std::string line = "";
		while(getline(shader_stream, line))
			shader_code += "\n" + line;
		shader_stream.close();
	}else{
		printf("ERROR: Impossible to open %s. Are you in the right directory?\n",
           file_path);
		getchar();
    shader_id_ = 0;
    return;
  }
  
  GLint result = GL_FALSE;
	int info_log_length;
  
  // Compile Vertex Shader
	printf("Compiling shader : %s\n", file_path);
	char const * vertex_source_pointer = shader_code.c_str();
	glShaderSource(shader_id_, 1, &vertex_source_pointer , NULL);
	glCompileShader(shader_id_);
  
	// Check Vertex Shader
	glGetShaderiv(shader_id_, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id_, GL_INFO_LOG_LENGTH, &info_log_length);
	if ( info_log_length > 0 ){
		std::vector<char> error_message(info_log_length+1);
		glGetShaderInfoLog(shader_id_, info_log_length, NULL, &error_message[0]);
		printf("%s\n", &error_message[0]);
    shader_id_ = 0;
    return;
	}
}

//! Destructor for the shader
/*!
 Releases memory on the GPU.
 */

Shader::~Shader(){
  glDeleteShader(shader_id_);
}

//! Get the id of the shader.

GLuint Shader::GetShaderId(){
  return shader_id_;
}
