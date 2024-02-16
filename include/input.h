/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef INPUT_H
#define INPUT_H

#include "glHeaders.h"
#include "graphics.h"
#include "window.h"

class Input {
    public:
        Input(Graphics* newGraphics, Window* newWindow);
        ~Input();
        static void KeyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods);
        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void InputStream();

    private:
        Graphics* glGraphics;
        Window* glWindow;
};
#endif