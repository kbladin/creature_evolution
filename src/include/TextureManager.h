#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

// C++
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <stdio.h>
// External
#include <GL/glew.h>

enum TextureType{
  STANDARD = 0, // Not procedural
  CHECKERBOARD = 1, // Procedural
  CIRCLES = 2 // Procedural
};

//! This class defines the material properties used for shading.
/*!
  The material has a diffuse texture which can be set to one of the textures
  created in the TextureManager. The name have to match. The material also
  has other properties like reflectance, specularity and shinyness,
  which can be set to make the appearance different when shading.
  The value of texture_diffuse_type tells whether the texture is of STANDARD=0
  type  which means it is read from an image file. Other types are
  CHECKERBOARD=1 which is a procedural texture.
*/

class Material {
public:
  Material();
  GLuint GetDiffuseTextureID();
  void SetDiffuseTexture(const char* texturename);
  
  float reflectance;
  float specularity;
  float shinyness;
  int texture_diffuse_type;
private:
  GLuint texture_diffuse_id_;
};

//! TextureManager is a singleton class which means it can be accessed from all around the application.
/*!
  Using this class, all textures can be loaded (providing an opengl context
  is created) in to graphics memory and then be reused for different
  objects in the scene. Currently there is only diffuse textures but this
  can be extended for use of normal-maps for example.
*/

class TextureManager {
public:
  static TextureManager* Instance();
  static void Destroy(void);

  void LoadTexture(const char* filename, const char* texturename);
  void FreeTexture(const char* texturename);
  void FreeAll();
  void BindTexture(const char* texturename);
  void BindTexture(GLuint texture_id);

  GLuint GetIDFromName(const char* texturename);

private:
  TextureManager();
  ~TextureManager();

  GLuint LoadBitmapFile(const char* filename);
  GLuint LoadDDSFile(const char* filename);

  std::map<std::string, GLuint> textures_;
  static TextureManager *instance_;
};

#endif // TEXTUREMANAGER_H