//
// Created by Kaolin on 25-Dec-24.
//

#include "Light.h"
Light::Light() : Light(1.0f,1.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f){}
Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
          GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity) : color(glm::vec3(red, green, blue)), ambientIntensity(aIntensity) {}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation) {
    glUniform3f(ambientColorLocation,color.x,color.y,color.z);
    glUniform1f(ambientIntensityLocation,ambientIntensity);
}

Light::~Light() {}
