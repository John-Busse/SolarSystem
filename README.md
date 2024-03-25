# OpenGL Project: Solar System (in beta)
## Rendering a solar system in OpenGL

## Project Description
This project is an effort in relearning OpenGL by remaking the first project from a Computer Graphics course I took at UNR in the Fall 2021 semester.

## Project plans
#### XML file
~~Use XML file with basic planet information for the sun, 8 planets, and pluto.~~ COMPLETE 2/14/24\
~~Add rings for Jupiter, Saturn, Uranus, and Neptune.~~ COMPLETE 2/14/24\
Add Major moons of Earth, Mars, Jupiter, Saturn, Uranus, Neptune, Pluto.\
Add consistent/accurate scale in planet size and distance.
#### Objects
~~.obj files for sphere, saturn ring, and smaller ring systems.~~ COMPLETE 2/14/24\
~~.jpg texture files for sun, 8 planets, pluto, saturn rings, smaller rings, and moons.~~ COMPLETE 2/14/24\
~~.mtl files for sun, 8 planets, pluto, saturn rings, smaller rings, and moons.~~ COMPLETE 2/14/24\
normal maps for sun, 8 planets, pluto, saturn rings, smaller rings, and moons.
#### Lighting/Shading
~~basic unlit shading~~ COMPLETE 2/14/24\
~~blinn-phong reflection model~~ COMPLETE 2/23/24\
implement dynamic shadows\
normal map lighting\
add transparency to rings
#### Background
~~clear color for background~~ COMPLETE 2/14/24\
add starry background
#### Controls
~~zoom in and out (W S)~~ COMPLETE 2/14/24\
~~update zoom to scale with planet radius~~ COMPLETE 3/25/24\
~~rotate horizontally (A D)~~ COMPLETE 2/14/24\
~~rotate vertically (R F)~~ COMPLETE 2/14/24\
~~select specific planet (0-9)~~ COMPLETE 2/14/24\
~~update planet selection to reset angle~~ COMPLETE 3/11/24\
~~reset viewing angle (spacebar) button implemented~~ COMPLETE 2/14/24\
~~update reset angle to the camera facing the sunlit side of the planet~~ COMPLETE 3/11/24
#### User interface
~~Include console output showing control options.~~ COMPLETE 2/14/24\
Add GUI to replace console output.\
Add updating planet information to GUI:\
-Which planet is selected, current zoom distance, horizontal and vertical angles.
#### Camera/Window
~~basic window at 800 x 600 resolution.~~\
update window to handle variable resolutions and fullscreen.

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
The building of the project is done using CMake, installation with apt-get may be necessary. 

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