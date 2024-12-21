#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>
#include "Mesh.h"
#include "Shader.h"

//window values
constexpr GLint WIDTH = 800;
constexpr GLint HEIGHT = 600;
constexpr const char* TITLE = "App";

constexpr float toRadians = 3.14159265f / 180.0f; // PI / 180

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

std::string vShaderPath = std::string(SHADER_DIR) + "shader.vert";
std::string fShaderPath = std::string(SHADER_DIR) + "shader.frag";

// Vertex shader
static const char* vShader = vShaderPath.c_str();

// Fragment shader
static const char* fShader = fShaderPath.c_str();


// a redundant comment to tell you that this method is for creating an object
void CreateObjects() {
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}


void CreateShaders() {
    Shader *shader1 = new Shader();
    shader1->CreateFromString(vShader, fShader);
    shaderList.push_back(*shader1);
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

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    const GLubyte* version = glGetString(GL_VERSION);
    printf("OpenGL Version: %s\n", version);

    glEnable(GL_DEPTH_TEST);

    //setup viewport size
    glViewport(0,0,bufferWidth,bufferHeight);

    CreateObjects();
    CreateShaders();

    GLuint uniformProjection = 0, uniformModel = 0;

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);

    // loop until window closed
    while (!glfwWindowShouldClose(mainWindow)) {
        // get and handle user input events
        glfwPollEvents();

        // clear window
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();

        glm::mat4 model(1.0f);

        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        // model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        meshList[0]->RenderMesh();

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    
    return 0; 
}

