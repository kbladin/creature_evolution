#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

// C++
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// External
#include <GL/glew.h>

class Shader;
class ShaderProgram;
class SimpleMvpShaderProgram;

class ShaderManager{
public:
	static ShaderManager* Instance();
  ShaderProgram* GetShaderFromName(const char* name);
  

private:
  ShaderManager();
	~ShaderManager();
  void AddAllShaders();
  void AddSimpleMvpShaderProgram();
  
  static ShaderManager* m_p_instance_;
  std::map<std::string, Shader*> shaders_;
  std::map<std::string, ShaderProgram*> shader_programs_;
};

class ShaderProgram{
public:
	ShaderProgram(Shader* vertex_shader = NULL,
                Shader* fragment_shader = NULL,
                Shader* geometry_shader = NULL,
                Shader* tesselation_shader = NULL);
	~ShaderProgram();
  
  GLuint getID();
  
  GLint GetAttribLocation(const char* name);
  GLint GetUniformLocation(const char* name);

  GLint mvp_loc_ = -1;
  GLint mv_loc_ = -1;
  GLint m_loc_ = -1;
  GLint v_loc_ = -1;
  
private:
  GLuint program_id_;
};

class Shader{
public:
	Shader(const char* file_path, int type);
	~Shader();
  
  GLuint GetShaderId();
private:  
  GLuint shader_id_;
};

#endif // SHADERMANAGER_H