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
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);

    ~Light();
private:
  glm::vec3 color;
  GLfloat ambientIntensity;
};



#endif //LIGHT_H
