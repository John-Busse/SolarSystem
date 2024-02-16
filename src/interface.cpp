/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "interface.h"

Interface::Interface() {
    cout    << "Solar System Project\n"
            << "Controls:\n"
            << "[W][S]:\tZoom camera in and out\n"
            << "[A][D]:\tRotate camera left and right\n"
            << "[R][F]:\tRotate camera up and down\n"
            << "[0-9]:\tSelect specific planet\n"
            << "[-][=]:\tAdjust simulation speed\n"
            << "[Space]:\tReset viewing angle\n";
}

Interface::~Interface() {

}