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
/*
  // Usage
  int LoadTexture(const char* szFilœename, int nTextureID = -1);
  int LoadTextureFromMemory(
    GLubyte* pData,
    int nWidth,
    int nHeight,
    int nBPP,
    int nTextureID = -1);
  void FreeTexture(int nID);
  void FreeAll(void);

  // Debug
  char* GetErrorMessage(void);
  int GetNumTextures(void);
  int GetAvailableSpace(void);
  int GetTexID(int nIndex);

  private:
  static TextureManager *instance_;
  char szErrorMessage[80];  // they arn't bugs, their features!
  int nNumTextures;
  int nAvailable;         // available space in the nTexID array
  int* nTexIDs;

  TextureManager();
  ~TextureManager();
  GLubyte* LoadBitmapFile(
    const char* filename,
    int& nWidth,
    int& nHeight,
    int& nBPP);
  GLubyte* LoadTargaFile(
    const char* filename,
    int& nWidth,
    int& nHeight,
    int& nBPP);
    */
};

#endif // TEXTUREMANAGER_H