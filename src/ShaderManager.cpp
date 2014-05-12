#include "ShaderManager.h"
#include "Scene.h"

///////////////////
// ShaderManager //
///////////////////

ShaderManager* ShaderManager::instance_ = NULL;

//! A part of the singleton pattern
/*!
 If this function is called for the first time, the constructor is called and
 the singleton is created.
 \return The one instance of the ShaderManager
 */
ShaderManager* ShaderManager::Instance() {
  if (!instance_)  // only allow one instance of class to be generated
    instance_ = new ShaderManager();
  return instance_;
}

//! ShaderManager constructor.
/*!
 First all Shaders are added and compiled by calling the function
 AddAllShaders(). Then all the individual ShaderPrograms are linked.
 These use the shaders added in the previous call.
*/

ShaderManager::ShaderManager() {
  AddAllShaders();
  AddSimpleMvpShaderProgram();
  AddBasicShaderProgram();
}

//! ShaderManager destructor
/*!
 First, all Shaders are deleted, then all ShaderPrograms.
*/

ShaderManager::~ShaderManager() {
  //Delete shaders
  std::map<std::string, Shader*>::iterator shader_iter = shaders_.begin();
  while (shader_iter != shaders_.end()) {
    delete shader_iter->second;
    shader_iter++;
  }
  //Delete ShaderPrograms
  std::map<std::string, ShaderProgram*>::iterator shader_program_iter =
      shader_programs_.begin();
  while (shader_program_iter != shader_programs_.end()) {
    delete shader_program_iter->second;
    shader_program_iter++;
  }
}

//! Add all shaders specified
/*!
 All the Shaders used by the program shall be added. First all Shaders are
 created (compiled) and then they are put in the std::map of Shaders.
*/

void ShaderManager::AddAllShaders() {
  
  std::stringstream preprocessor;
  preprocessor << "#version 330 core \n";

  std::stringstream preprocessor_basic_frag;
  preprocessor_basic_frag << preprocessor.str() << "#define N_LIGHTS " << Scene::N_LIGHTS;

  // Create shaders
  Shader* simple_mvp_vert = new Shader(
      "data/shaders/mvp.vert",
      preprocessor.str().c_str(),
      GL_VERTEX_SHADER);
  Shader* simple_mvp_frag = new Shader(
      "data/shaders/simple.frag",
      preprocessor.str().c_str(),
      GL_FRAGMENT_SHADER);
  Shader* basic_vert = new Shader(
      "data/shaders/basic.vert",
      preprocessor.str().c_str(),
      GL_VERTEX_SHADER);
  Shader* basic_frag = new Shader(
      "data/shaders/basic.frag",
      preprocessor_basic_frag.str().c_str(),
      GL_FRAGMENT_SHADER);
  // Put shaders in the map
  shaders_.insert(StringShaderPair("Simple_MVP_Vert", simple_mvp_vert));
  shaders_.insert(StringShaderPair("Simple_MVP_Frag", simple_mvp_frag));
  shaders_.insert(StringShaderPair("Basic_Vert", basic_vert));
  shaders_.insert(StringShaderPair("Basic_Frag", basic_frag));
}

//! Add the specific ShaderProgram Simple_MVP
/*!
 This is a specific creator function for the shader Simple_MVP. This function
 relies on that the specific Shaders used are already compiled. Therefore they
 can be picked from the std::map of Shaders and then put in the constructor of
 the new ShaderProgram. The ShaderProgram is then inserted in the
 ShaderManager. All the specific locations also needs to be added, these are
 then called by name instead of GLuint.
*/

void ShaderManager::AddSimpleMvpShaderProgram(){
  // Create ShaderProgram
  ShaderProgram* simple_mvp_shader_program =
    new ShaderProgram(shaders_["Simple_MVP_Vert"],
                      shaders_["Simple_MVP_Frag"]);
  // The name with which to refer to the ShaderProgram
  const char* shader_program_name = "Simple_MVP";
  // Put ShaderProgram in the map
  shader_programs_.insert(StringShaderProgPair(
      shader_program_name,
      simple_mvp_shader_program) );
  // Create all locations
  shader_programs_[shader_program_name]->CreateUniformLocation("MVP");
}

//! Add the specific ShaderProgram Basic
/*!
 This is a specific creator function for the Shader "Basic". This function
 relies
 on that the specific Shaders used are already compiled. Therefore they can be
 picked from the std::map of shaders and then put in the constructor of the new
 ShaderProgram. The ShaderProgram is then inserted in the ShaderManager. All
 the specific locations also needs to be added, these are then called by name
 instead of GLuint.
 */

void ShaderManager::AddBasicShaderProgram(){
  // Create ShaderProgram
  ShaderProgram* simple_mvp_shader_program =
  new ShaderProgram(shaders_["Basic_Vert"],
                    shaders_["Basic_Frag"]);
  // The name with which to refer to the ShaderProgram
  const char* shader_program_name = "Basic";
  // Put ShaderProgram in the map
  shader_programs_.insert(StringShaderProgPair(
      shader_program_name,
      simple_mvp_shader_program) );
  // Create all locations
  shader_programs_[shader_program_name]->CreateUniformLocation("MVP");
  shader_programs_[shader_program_name]->CreateUniformLocation("MV");
  shader_programs_[shader_program_name]->CreateUniformLocation("M");
  shader_programs_[shader_program_name]->CreateUniformLocation("V");
  shader_programs_[shader_program_name]->CreateUniformLocation("far_clipping");

  shader_programs_[shader_program_name]->CreateUniformLocation(
          "light_data"); // Containt all lights
  shader_programs_[shader_program_name]->CreateUniformLocation(
          "texture_sampler2D");
  shader_programs_[shader_program_name]->CreateUniformLocation(
          "material.reflectance");
  shader_programs_[shader_program_name]->CreateUniformLocation(
          "material.specularity");
  shader_programs_[shader_program_name]->CreateUniformLocation(
          "material.shinyness");
    shader_programs_[shader_program_name]->CreateUniformLocation(
          "material.texture_type");
}

//! Used for accessing the ShaderPrograms.
/*!
 Instead of relying on GLints, names are used for getting ShaderPrograms.
\param name is the name key of the wanted ShaderProgram
\return A pointer to the corresponding ShaderProgram
*/

ShaderProgram* ShaderManager::GetShaderProgramFromName(const char* name) {
  return shader_programs_[name];
}

//! Used for binding ShaderPrograms.
/*!
 Bind the ShaderProgram specified by the name key. If the ShaderProgram is
 not found, the default ShaderProgram is bound.
 \param The name key of the ShaderProgram to bind.
 */

void ShaderManager::UseProgram(const char* name) {
  glUseProgram(shader_programs_[name]->getID());
}

//! Used for unbinding ShaderPrograms.
/*!
 Unbind the current ShaderProgram. The same as binding the default shader
 program (0)
*/

void ShaderManager::UnbindCurrentShader() {
  glUseProgram(0);
}

///////////////////
// ShaderProgram //
///////////////////

//! Constructor for the ShaderProgram class
/*!
 All the shaders passed in the arguments gets linked in to a ShaderProgram.
 \param Pointers to the shaders to be linked in the order vertex, fragment,
 geometry and tesselation shader. Vertex and fragment shaders are the only
 ones that are needed.
 */

ShaderProgram::ShaderProgram(Shader* vertex_shader,
                             Shader* fragment_shader,
                             Shader* geometry_shader,
                             Shader* tesselation_shader) {
  if (vertex_shader == NULL || fragment_shader == NULL) {
    program_id_ = 0;
    std::cout << "ERROR: ShaderProgram could not be created. " <<
        "Vertex shader and fragment shader are required!" << std::endl;
    return;
  }

  // Link the program
  printf("Linking ShaderProgram\n");
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
		glGetProgramInfoLog(
        program_id_,
        info_log_length,
        NULL,
        &program_error_message[0]);
		printf("%s\n", &program_error_message[0]);
    //if linking the shaders failed, set to 0
    if(result == GL_FALSE)
      program_id_ = 0;
    return;
	}
}

//! Delete the ShaderProgram.

ShaderProgram::~ShaderProgram(){
  glDeleteProgram(program_id_);
}

//! Create a location for an attribute in the ShaderProgram.
/*!
 The name of the attribute needs to be specified in the source code of the
 shader. If it is not found it can not be created and an error message is
 printed. If it is found, the location is added to the std::map of attributes.
 Then they can be accessed via name instead of GLint.
 \param name is the name of the attribute for which to create the location.
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

//! Create a location for a uniform in the ShaderProgram.
/*!
 The name of the uniform needs to be specified in the source code of the
 shader. If it is not found it can not be created and an error message is
 printed. If it is found, the location is added to the std::map of uniforms.
 Then they can be accessed via name instead of GLint.
 \param name is the name of the uniform for which to create the location.
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
 \param name is the key of the uniform.
 \param v0 is the value to set.
*/

// Uniforms
void ShaderProgram::Uniform1f(const char* name, GLfloat v0){
  glUniform1f(uniform_locations_[name], v0);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param v0 is the value to set.
 \param v1 is the value to set.
*/

void ShaderProgram::Uniform2f(const char* name, GLfloat v0, GLfloat v1){
  glUniform2f(uniform_locations_[name], v0, v1);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
*/

void ShaderProgram::Uniform3f(
    const char* name,
    GLfloat v0,
    GLfloat v1,
    GLfloat v2){
  glUniform3f(uniform_locations_[name], v0, v1, v2);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
*/

void ShaderProgram::Uniform4f(
    const char* name,
    GLfloat v0,
    GLfloat v1,
    GLfloat v2,
    GLfloat v3){
  glUniform4f(uniform_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param v0 is the value to set.
*/

void ShaderProgram::Uniform1i(const char* name, GLint v0){
  glUniform1i(uniform_locations_[name], v0);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param v0 is the value to set.
 \param v1 is the value to set.
 */

void ShaderProgram::Uniform2i(const char* name, GLint v0, GLint v1){
  glUniform2i(uniform_locations_[name], v0, v1);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
 */

void ShaderProgram::Uniform3i(const char* name, GLint v0, GLint v1, GLint v2){
  glUniform3i(uniform_locations_[name], v0, v1, v2);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
 */

void ShaderProgram::Uniform4i(
    const char* name,
    GLint v0,
    GLint v1,
    GLint v2,
    GLint v3){
  glUniform4i(uniform_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform1fv(
    const char* name,
    GLsizei count,
    const GLfloat *value){
  glUniform1fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform2fv(
    const char* name,
    GLsizei count,
    const GLfloat *value){
  glUniform2fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform3fv(
    const char* name,
    GLsizei count,
    const GLfloat *value){
  glUniform3fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform4fv(
    const char* name,
    GLsizei count,
    const GLfloat *value){
  glUniform4fv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform1iv(
    const char* name,
    GLsizei count,
    const GLint *value){
  glUniform1iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform2iv(
    const char* name,
    GLsizei count,
    const GLint *value){
  glUniform2iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform3iv(
    const char* name,
    GLsizei count,
    const GLint *value){
  glUniform3iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of vectors following.
 \param value is the value to set.
 */

void ShaderProgram::Uniform4iv(
    const char* name,
    GLsizei count,
    const GLint *value){
  glUniform4iv(uniform_locations_[name], count, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of matrices following.
 \param transpose is true if the matrix is transposed
 \param value is the value to set.
 */

void ShaderProgram::UniformMatrix2fv(
    const char* name,
    GLsizei count,
    GLboolean transpose,
    const GLfloat *value){
  glUniformMatrix2fv(uniform_locations_[name], count, transpose, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of matrices following.
 \param transpose is true if the matrix is transposed
 \param value is the value to set.
 */

void ShaderProgram::UniformMatrix3fv(
    const char* name,
    GLsizei count,
    GLboolean transpose,
    const GLfloat *value){
  glUniformMatrix3fv(uniform_locations_[name], count, transpose, value);
}

//! Wrapper for OpenGL's function for uniform data.
/*!
 Set data for the specific uniform.
 \param name is the key of the uniform
 \param count is the number of matrices following.
 \param transpose is true if the matrix is transposed
 \param value is the value to set.
 */

void ShaderProgram::UniformMatrix4fv(
    const char* name,
    GLsizei count,
    GLboolean transpose,
    const GLfloat *value){
  glUniformMatrix4fv(uniform_locations_[name], count, transpose, value);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute.
 \param v0 is the value to set.
 */

// Attributes
void ShaderProgram::VertexAttrib1f(const char* name, GLfloat v0){
  glVertexAttrib1f(attribute_locations_[name], v0);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v0 is the value to set.
 \param v1 is the value to set.
 */

void ShaderProgram::VertexAttrib2f(const char* name, GLfloat v0, GLfloat v1){
  glVertexAttrib2f(attribute_locations_[name], v0, v1);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
 */

void ShaderProgram::VertexAttrib3f(
    const char* name,
    GLfloat v0,
    GLfloat v1,
    GLfloat v2){
  glVertexAttrib3f(attribute_locations_[name], v0, v1, v2);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
 \param v3 is the value to set.
 */

void ShaderProgram::VertexAttrib4f(
    const char* name,
    GLfloat v0,
    GLfloat v1,
    GLfloat v2,
    GLfloat v3){
  glVertexAttrib4f(attribute_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
 \param v3 is the value to set.
 */

void ShaderProgram::VertexAttribI4i(
    const char* name,
    GLint v0,
    GLint v1,
    GLint v2,
    GLint v3){
  glVertexAttribI4i(attribute_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v0 is the value to set.
 \param v1 is the value to set.
 \param v2 is the value to set.
 \param v3 is the value to set.
 */

void ShaderProgram::VertexAttribI4ui(
    const char* name,
    GLuint v0,
    GLuint v1,
    GLuint v2,
    GLuint v3){
  glVertexAttribI4ui(attribute_locations_[name], v0, v1, v2, v3);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v is the value to set.
*/

void ShaderProgram::VertexAttrib1fv(const char* name, const GLfloat *v){
  glVertexAttrib1fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v is the value to set.
*/

void ShaderProgram::VertexAttrib2fv(const char* name, const GLfloat *v){
  glVertexAttrib2fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v is the value to set.
 */

void ShaderProgram::VertexAttrib3fv(const char* name, const GLfloat *v){
  glVertexAttrib3fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v is the value to set.
*/

void ShaderProgram::VertexAttrib4fv(const char* name, const GLfloat *v){
  glVertexAttrib4fv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v is the value to set.
 */

void ShaderProgram::VertexAttribI4iv(const char* name, const GLint *v){
  glVertexAttribI4iv(attribute_locations_[name], v);
}

//! Wrapper for OpenGL's function for attribute data.
/*!
 Set data for the specific attribute.
 \param name is the key of the attribute
 \param v is the value to set.
*/

void ShaderProgram::VertexAttribI4uiv(const char* name, const GLuint *v){
  glVertexAttribI4uiv(attribute_locations_[name], v);
}

//! Get the id for the ShaderProgram
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
 Compiles the Shader from the file path.
 \param file_path is the path for where the Shader source is to be found.
 \param type is the type of the Shader. Can be GL_VERTEX_SHADER or
 GL_FRAGMENT_SHADER.
 */

Shader::Shader(const char* file_path, const char* preprocessor_code, int type){
  // Create the shader
  shader_id_ = glCreateShader(type);


  if (shader_id_ == 0) {
    std::cout << "ERROR: Invalid shader type: " << type << "!" << std::endl;
    return;
  }
  // Read the Shader code from the file
	std::string shader_code = preprocessor_code;
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
    //if compiling the shader failed, set to 0
    if(result == GL_FALSE)
      shader_id_ = 0;
    return;
	}

}

//! Destructor for the shader
/*!
 Releases memory on the GPU.
*/

Shader::~Shader(){
  glDeleteShader
  (shader_id_);
}


//! Get the id of the Shader.

GLuint Shader::GetShaderId(){
  return shader_id_;
}
