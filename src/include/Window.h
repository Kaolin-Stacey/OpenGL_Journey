#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>


class Window {
    public:
        Window();
        Window(GLint windowWidth, GLint windowHeight);

        int Initialise();
        GLfloat getBufferWidth() { return bufferWidth; }
        GLfloat getBufferHeight() { return bufferHeight; }

        bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
        void swapBuffers() { glfwSwapBuffers(mainWindow); }

        ~Window();
    private:
        GLFWwindow *mainWindow;
        GLint width, height;
        const char* title = "App";
        GLint bufferWidth, bufferHeight;
};

#endif