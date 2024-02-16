/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef WINDOW_H
#define WINDOW_H

#include "glHeaders.h"

class Window {
    public:
        Window();
        ~Window();

        bool Init(const string& windowName, int* width, int* height);
        void Swap();

        bool ShouldClose();

        void ReshapeCallback();

        GLFWwindow* GetWindow();

    private:
        GLFWwindow *thisWindow;
};
#endif