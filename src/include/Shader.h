#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>

class Shader {
public:
    Shader();

    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

    static std::string ReadFile(const char* fileLocation);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();

    void UseShader();
    void ClearShader();
    ~Shader();
private:
    GLuint shaderID, uniformModel, uniformProjection, uniformView;
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

#endif