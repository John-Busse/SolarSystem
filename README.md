# OpenGL Project: Solar System (in beta)
Rendering a solar system in OpenGL

# Project Description
This project is an effort in relearning OpenGL by remaking the first project from a Computer Graphics course I took at UNR in the Fall 2021 semester.

# Future plans:
-Update uv data of sphere object file for texture mapping.\
-Update planetary scale and add moons in xml file.\
-Add dynamic lighting and shadows.\
-Add a starry background.\
-Add a proper UI showing user controls, instead of having them posted in console output.\
-Update Camera and Window drivers to handle variable resolutions and fullscreen.\

# Dependencies, Building, and Running
I'm including the instructions to build and run this program on your own.

## Dependency Instructions
For both of the operating systems to run this project installation of these programs are required:
[GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), [GLFW](https://www.glfw.org/), [ASSIMP](https://www.assimp.org/), [GRAPHICSMAGICK](http://www.graphicsmagick.org/)
You'll also need a C++ compiler. I used the MinGW g++ compiler.

### Ubuntu/Linux
```linux terminal
sudo apt-get install libglew-dev libglm-dev libglfw3-dev libopengl0 assimp-utils libassimp-dev libassimp5 graphicsmagick libmagick++-dev
```

## Building and Running
This project is designed to be built in CMake to generate the makefile and handle new files being added to the src and include directories.

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. 

```linux terminal:
~navigate to the folder containing this readme~
mkdir build
cd build
cmake ..
make
./Solar
```

### External Credits
This project makes use of the [TinyXML2](https://github.com/leethomason/tinyxml2) library written by Lee Thomason. The header and driver for that library are included in this repository.

The framework of this code is based around chapter exercises from the book "Computer Graphics Programming in OpenGL with C++" Second Edition by V. Scott Gordon and John Clevenger.
