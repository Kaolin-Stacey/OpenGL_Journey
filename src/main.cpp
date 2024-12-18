#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cmath>

//window dimensions
constexpr GLint WIDTH = 800;
constexpr GLint HEIGHT = 600;

//window name
constexpr const char* TITLE = "App";

GLuint VAO, VBO, shader, uniformXMove;

bool direction = true;
float triOffset = 0.0f;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

// Vertex shader
static const char* vShader = "                                          \n\
#version 330                                                            \n\
layout (location = 0) in vec3 pos;                                      \n\
uniform float xMove;                                                    \n\
void main() {                                                           \n\
    gl_Position = vec4(0.4*pos.x+xMove, 0.4*pos.y, pos.z, 1.0);         \n\
}";

// Fragment shader
static const char* fShader = "                                          \n\
#version 330                                                            \n\
out vec4 color;                                                         \n\
void main() {                                                           \n\
    color = vec4(1.0, 0.0, 0.0, 1.0);                                   \n\
}";

// a redundant comment to tell you that this method is for creating a triangle
void CreateTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);

}

void CompileShaders() {
    shader = glCreateProgram();

    if (!shader) {
        printf("Error creating shader program\n");
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    uniformXMove = glGetUniformLocation(shader, "xMove");
}

int main() {
    //initialise GLFW
    if(!glfwInit()){
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }

    //setup GLFW window properties

    //opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //core profile = no backwards compatibility, and allow forwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (!mainWindow) {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }

    // get buffer size info
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // allow modern extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        printf("GLEW initialisation failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    //setup viewport size
    glViewport(0,0,bufferWidth,bufferHeight);

    CreateTriangle();
    CompileShaders();

    // loop until window closed
    while (!glfwWindowShouldClose(mainWindow)) {
        // get and handle user input events
        glfwPollEvents();

        if (direction) {
            triOffset += triIncrement;
        } else {
            triOffset -= triIncrement;
        }

        if (abs(triOffset)>=triMaxOffset) {
            direction = !direction;
        }

        // clear window
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glUniform1f(uniformXMove, triOffset);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);


        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    
    return 0; 
}