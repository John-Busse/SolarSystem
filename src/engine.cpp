/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/

#include "engine.h"

//windowed engine constructor
Engine::Engine(string name, int width, int height) {
    wName = name;
    wWidth = width;
    wHeight = height;
    fullscreen = false;
    lastFrame = glfwGetTime();
	
	vertFile = const_cast<char*>("shaders/vert.glsl");
	fragFile = const_cast<char*>("shaders/frag.glsl");
}

//fullscreen engine constructor
Engine::Engine(string name) {
    wName = name;
    wWidth = 0;
    wHeight = 0;
    fullscreen = true;
}

//deconstructor
Engine::~Engine() {
    delete glWindow;
	glWindow = NULL;
	delete glGraphics;
	glGraphics = NULL;
	delete vertFile;
	vertFile = NULL;
	delete fragFile;
	fragFile = NULL;
}

bool Engine::Init(vector<Planet>& planetInfo) {
    //Start a window
    glWindow = new Window();
    if (!glWindow->Init(wName, &wWidth, &wHeight)) {
        cerr << "The window failed to initialize" << endl;
        return false;
    }

    // start the graphics
    glGraphics = new Graphics(planetInfo);
    if (!glGraphics->Init(wWidth, wHeight, vertFile, fragFile)) {
        cerr << "The graphics failed to initialize" << endl;
        return false;
    }

    //start the input manager
    glInput = new Input(glGraphics, glWindow);

    return true;
}

void Engine::Run() {
    while(!glWindow->ShouldClose()) {
        glGraphics->Render(GetDT());
        glWindow->Swap();
        glInput->InputStream();
        glfwPollEvents();
    }
}

/*  //This function will help with resizing the window
void Engine::WindowReshapeCallback(int newWidth, int newHeight) {
    aspect = (float)newWidth / (float)newHeight;    //new size provided by callback
    glViewport(0, 0, newWidth, newHeight);
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}*/

float Engine::GetDT() {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    return deltaTime;
}
