#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

//window dimensions
constexpr GLint WIDTH = 800;
constexpr GLint HEIGHT = 600;
constexpr const char* TITLE = "App";

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

    // loop until window closed
    while (!glfwWindowShouldClose(mainWindow)) {
        // get and handle user input events
        glfwPollEvents();

        // clear window
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    
    return 0; 
}