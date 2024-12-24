//
// Created by Kaolin on 23-Dec-24.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL\glew.h>
#include "stb_image.h"


class Texture {
public:
  Texture(const char* fileLoc);
  Texture();
  ~Texture();
  void LoadTexture();
  void UseTexture();
  void ClearTexture();

private:
  GLuint textureID;
  int width, height, bitDepth;

  const char* fileLocation;
};



#endif //TEXTURE_H
