//
// Created by Kaolin on 25-Dec-24.
//

#ifndef LIGHT_H
#define LIGHT_H

#include <GL\glew.h>
#include <glm.hpp>

class Light {
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
          GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
        GLfloat diffuseIntensityLocation, GLfloat directionLocation);

    ~Light();
private:
  glm::vec3 color;
  GLfloat ambientIntensity;

  glm::vec3 direction;
  GLfloat diffuseIntensity;
};



#endif //LIGHT_H
