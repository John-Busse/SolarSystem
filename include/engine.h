/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef ENGINE_H
#define ENGINE_H

#include "glHeaders.h"

#include "window.h"
#include "graphics.h"
#include "input.h"

class Engine {
    public:
        Engine(string name, int width, int height);
        Engine(string name);
        ~Engine();

        bool Init(vector<Planet>& planetinfo);
        void Run();
        void Display(double currentTime);
        void WindowReshapeCallback(int, int);

    private:
        //time functions
        float GetDT();
        long long GetTime();

        //window variables
        Window *glWindow;
        string wName;
        int wWidth;
        int wHeight;
        bool fullscreen;

        //graphics variables
        Graphics *glGraphics;
        bool running;

        //input variables
        Input* glInput;

        //time variables
        float deltaTime, currentFrame, lastFrame;
};

#endif
