/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "input.h"

Input::Input(Graphics* newGraphics, Window* newWindow) {
    glGraphics = newGraphics;
    glWindow = newWindow;
    glfwSetWindowUserPointer(glWindow->GetWindow(), this);
    glfwSetKeyCallback(glWindow->GetWindow(), KeyCallbackStatic);
    glfwSetInputMode(glWindow->GetWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);
}

Input::~Input() {
    delete glGraphics;
    glGraphics = NULL;
    delete glWindow;
    glWindow = NULL;
}

//GLFW requires a static function to handle key callbacks
// but static functions can't access non-static members
// so we use this function to bind the static key callback
// with the nonstatic key callback function
void Input::KeyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Input* that = static_cast<Input*>(glfwGetWindowUserPointer(window));
    that->KeyCallback(window, key, scancode, action, mods);
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /*keybinds:
    WS: Zoom in and out (adjust radius)
    AD: Rotate left and right (adjust theta)
    RF: Rotate up and down (adjust phi)
    number keys: select specific planet
    +- keys: adjust simulation speed
    space: reset angle*/

    //W S: Move in and out
    if (key == GLFW_KEY_W || key == GLFW_KEY_S) {
        glGraphics->CameraMoveZ(key == GLFW_KEY_S);
    }
    //A D: Rotate left and right
    if (key == GLFW_KEY_A || key == GLFW_KEY_D) {
        glGraphics->CameraMoveX(key == GLFW_KEY_D);
    }
    if (key == GLFW_KEY_R || key == GLFW_KEY_F) {
        glGraphics->CameraMoveY(key == GLFW_KEY_F);
    }
    // Number keys: select specific planet
    if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9 && action == GLFW_PRESS) {
        //since the key codes are stored in order as numbers
        glGraphics->SetPlanet(key - GLFW_KEY_0);
    }
    // Minus key: slow down simulation speed
    if ((key == GLFW_KEY_KP_SUBTRACT || key == GLFW_KEY_MINUS) && action == GLFW_PRESS) {
        glGraphics->ChangeSpeed(false);
    }
    // Plus key: speed up simulation speed
    if ((key == GLFW_KEY_KP_ADD || key == GLFW_KEY_EQUAL) && action == GLFW_PRESS) {
        glGraphics->ChangeSpeed(true);
    }
    // spacebar: reset angle
    if ((key == GLFW_KEY_SPACE && action == GLFW_PRESS))  {
        glGraphics->ResetAngle();
    }
}