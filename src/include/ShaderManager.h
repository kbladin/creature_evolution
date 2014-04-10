#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

// C++
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

// External
#include <GL/glew.h>

class Shader;
class ShaderProgram;
class SimpleMvpShaderProgram;

typedef std::pair<std::string, Shader*> StringShaderPair;
typedef std::pair<std::string, ShaderProgram*> StringShaderProgPair;

//! The ShaderManager handles all the Shaders and ShaderPrograms.
/*!
  This class uses the singleton pattern which makes it accessable from all
  around the program.
*/

class ShaderManager{
public:
	static ShaderManager* Instance();
  ShaderProgram* GetShaderProgramFromName(const char* name);
  void UseProgram(const char* name);
  void UnbindCurrentShader();
private:
  ShaderManager();
	~ShaderManager();
  void AddAllShaders();
  void AddSimpleMvpShaderProgram();
  void AddBasicShaderProgram();
  
  static ShaderManager* instance_;
  std::map<std::string, Shader*> shaders_;
  std::map<std::string, ShaderProgram*> shader_programs_;
};

//! A ShaderProgram is the result of linked Shaders.

class ShaderProgram{
public:
	ShaderProgram(Shader* vertex_shader = NULL,
                Shader* fragment_shader = NULL,
                Shader* geometry_shader = NULL,
                Shader* tesselation_shader = NULL);
	~ShaderProgram();
  
  GLuint getID();
  void CreateAttribLocation(const char* name);
  void CreateUniformLocation(const char* name);
  
  // Using the std::map it is enough with the name to set data.
  // No locations needed.
  void Uniform1f(const char* name, GLfloat v0);
  void Uniform2f(const char* name, GLfloat v0, GLfloat v1);
  void Uniform3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2);
  void Uniform4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
  void Uniform1i(const char* name, GLint v0);
  void Uniform2i(const char* name, GLint v0, GLint v1);
  void Uniform3i(const char* name, GLint v0, GLint v1, GLint v2);
  void Uniform4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3);
  void Uniform1fv(const char* name, GLsizei count, const GLfloat *value);  
  void Uniform2fv(const char* name, GLsizei count, const GLfloat *value);  
  void Uniform3fv(const char* name, GLsizei count, const GLfloat *value);  
  void Uniform4fv(const char* name, GLsizei count, const GLfloat *value);  
  void Uniform1iv(const char* name, GLsizei count, const GLint *value);  
  void Uniform2iv(const char* name, GLsizei count, const GLint *value);  
  void Uniform3iv(const char* name, GLsizei count, const GLint *value);  
  void Uniform4iv(const char* name, GLsizei count, const GLint *value);
  void UniformMatrix2fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value); 
  void UniformMatrix3fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value); 
  void UniformMatrix4fv(const char* name, GLsizei count, GLboolean transpose, const GLfloat *value);

  void VertexAttrib1f(const char* name, GLfloat v0);
  void VertexAttrib2f(const char* name, GLfloat v0, GLfloat v1);
  void VertexAttrib3f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2);
  void VertexAttrib4f(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
  void VertexAttribI4i(const char* name, GLint v0, GLint v1, GLint v2, GLint v3);
  void VertexAttribI4ui(const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
  void VertexAttrib1fv(const char* name, const GLfloat *v);
  void VertexAttrib2fv(const char* name, const GLfloat *v);
  void VertexAttrib3fv(const char* name, const GLfloat *v);
  void VertexAttrib4fv(const char* name, const GLfloat *v);
  void VertexAttribI4iv(const char* name, const GLint *v);
  void VertexAttribI4uiv(const char* name, const GLuint *v);
  
private:
  GLuint program_id_;
  std::map<std::string, GLint> uniform_locations_;
  std::map<std::string, GLint> attribute_locations_;
};

//! A Shader is compiled from source code in a shader file.
/*!
 A Shader does not work by itself. They need to be compiled in to a
 ShaderProgram.
*/
class Shader{
public:
	Shader(const char* file_path, int type);
	~Shader();
  GLuint GetShaderId();
private:  
  GLuint shader_id_;
};

#endif // SHADERMANAGER_H
