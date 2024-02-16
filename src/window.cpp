/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "window.h"

Window::Window() {
    thisWindow = NULL;
}

Window::~Window() {
    glfwDestroyWindow(thisWindow);
    thisWindow = NULL;
    glfwTerminate();
}

bool Window::Init(const string &wName, int* wWidth, int* wHeight) {
    //Initialize GLFW
    if (!glfwInit()) {
        cerr << "glfw failed to initialize" << endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    thisWindow = glfwCreateWindow(*wWidth, *wHeight, wName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(thisWindow);

    glfwSwapInterval(1);

    return true;
}

void Window::Swap() {
    glfwSwapBuffers(thisWindow);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(thisWindow);
}

GLFWwindow* Window::GetWindow() {
    return thisWindow;
}