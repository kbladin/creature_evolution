#include "ShaderManager.h"

///////////////////
// ShaderManager //
///////////////////
ShaderManager* ShaderManager::m_p_instance_ = NULL;

ShaderManager* ShaderManager::Instance() {
	if (!m_p_instance_) // only allow one instance of class to be generated
		m_p_instance_ = new ShaderManager();
	return m_p_instance_;
}

ShaderManager::ShaderManager(){
  AddAllShaders();
  AddSimpleMvpShaderProgram();
}

ShaderManager::~ShaderManager(){
  
  std::map<std::string, Shader*>::iterator shader_iter = shaders_.begin();
  while (shader_iter != shaders_.end()) {
    delete shader_iter->second;
    shader_iter++;
  }
  std::map<std::string, ShaderProgram*>::iterator shader_program_iter = shader_programs_.begin();
  while (shader_program_iter != shader_programs_.end()) {
    delete shader_program_iter->second;
    shader_program_iter++;
  }
}

void ShaderManager::AddAllShaders(){
  // Create shaders
  Shader* simple_mvp_vert = new Shader("mvp.vert",GL_VERTEX_SHADER);
  Shader* simple_mvp_frag = new Shader("simple.frag",GL_FRAGMENT_SHADER);
  
  // Put shaders in the map
  shaders_.insert( std::pair<std::string, Shader*>("Simple_MVP_Vert", simple_mvp_vert) );
  shaders_.insert( std::pair<std::string, Shader*>("Simple_MVP_Frag", simple_mvp_frag) );
}

void ShaderManager::AddSimpleMvpShaderProgram(){
  // Create shader program
  ShaderProgram* simple_mvp_shader_program =
    new ShaderProgram(
                      shaders_["Simple_MVP_Vert"],
                      shaders_["Simple_MVP_Frag"]
                      );
  const char* shader_program_name = "Simple_MVP";
  // Put shader programs in the map
  shader_programs_.insert( std::pair<std::string, ShaderProgram*> (shader_program_name, simple_mvp_shader_program) );
  // Get all locations
  shader_programs_[shader_program_name]->mvp_loc_ =
    shader_programs_[shader_program_name]->GetUniformLocation("MVP");
}

ShaderProgram* ShaderManager::GetShaderFromName(const char* name){
  return shader_programs_[name];
}

///////////////////
// ShaderProgram //
///////////////////
ShaderProgram::ShaderProgram(Shader* vertex_shader,
                             Shader* fragment_shader,
                             Shader* geometry_shader,
                             Shader* tesselation_shader){
  // Link the program
	printf("Linking program\n");
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

ShaderProgram::~ShaderProgram(){
  glDeleteProgram(program_id_);
}

GLint ShaderProgram::GetAttribLocation(const char* name){
  GLint loc = glGetAttribLocation(program_id_, name);
  if (loc == -1) {
    std::cout << "Unknown Attrib name: " << name << std::endl;
  }
  return loc;
}

GLint ShaderProgram::GetUniformLocation(const char* name){
  GLint loc = glGetUniformLocation(program_id_, name);
  if (loc == -1) {
    std::cout << "Unknown Uniform name: " << name << std::endl;
  }
  return loc;
}

GLuint ShaderProgram::getID(){
  return program_id_;
}

////////////
// Shader //
////////////
Shader::Shader(const char* file_path, int type){
  
  // Create the shader
  shader_id_ = glCreateShader(type);
  if (shader_id_ == 0) {
    std::cout <<
    "ERROR: Invalid shader type in Shader constructor." <<
    std::endl;
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
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", file_path);
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

Shader::~Shader(){
  glDeleteShader(shader_id_);
}

GLuint Shader::GetShaderId(){
  return shader_id_;
}

