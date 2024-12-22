#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Window {
public:
    Window();
    Window(GLint windowWidth, GLint windowHeight);

    int Initialise();
    GLfloat getBufferWidth() const { return bufferWidth; }
    GLfloat getBufferHeight() const { return bufferHeight; }

    bool getShouldClose() const { return glfwWindowShouldClose(mainWindow); }

    bool* getKeys() { return keys; }
    GLfloat getXChange();
    GLfloat getYChange();

    void swapBuffers() const { glfwSwapBuffers(mainWindow); }

    ~Window();
private:
    GLFWwindow *mainWindow;
    GLint width, height;

    const char* title = "App";

    int bufferWidth, bufferHeight;

    bool keys[1024];

    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;


    void createCallbacks() const;
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

#endif