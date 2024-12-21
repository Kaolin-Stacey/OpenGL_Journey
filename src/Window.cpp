#include "Window.h"
#include <iostream> // For better logging

Window::Window() : width(800), height(600) { }

Window::Window(GLint windowWidth, GLint windowHeight) : width(windowWidth), height(windowHeight) { }

int Window::Initialise()
{
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed!" << std::endl;
        return 1;
    }

    // Setup GLFW window properties
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!mainWindow) {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extension features
    glewExperimental = GL_TRUE;
    
    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed!" << std::endl;
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    return 0;
}

Window::~Window()
{
    // Clean up and terminate GLFW
    if (mainWindow) {
        glfwDestroyWindow(mainWindow);
    }
    glfwTerminate();
}
