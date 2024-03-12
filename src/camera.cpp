/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "camera.h"

Camera::Camera() {
}

Camera::Camera(int& width, int& height) {
    radius = 5.0f;      // max radius: 50 units
    theta = 270.0f;     //  0-360 degrees
    phi = 90.0f;        // 0-180 degrees
    camPos = glm::vec3(-0.0f, -0.0f, -50.0f);   //Where the camera is
    focusPos = glm::vec3(0.0f, 0.0f, 0.0f);     //Shift down Y to reveal perspective

    projection = glm::perspective(  1.0472f,        //FoV, ~60 degrees
                                    (float)width / (float)height,   //aspect ratio
                                    0.1f,           //near plane distance
                                    10000.0f);      //far plane distance
}

Camera::~Camera() {

}

glm::vec3 Camera::GetCamPos() {
    return camPos;
}

glm::vec3 Camera::GetFocus() {
    return focusPos;
}

glm::mat4 Camera::GetView() {
    return glm::lookAt( camPos,
                        focusPos,
                        UPAXIS);
}

//returns projection matrix (perspective)
glm::mat4 Camera::GetProj() {
    return projection;
}

void Camera::SetPos(glm::vec4 position) {
    camPos = glm::vec3( position.x + radius * sin(glm::radians(phi)) * cos(glm::radians(theta)), 
                        position.y + radius * cos(glm::radians(phi)),
                        position.z + radius * sin(glm::radians(phi)) * sin(glm::radians(theta)));
    focusPos = glm::vec3(position.x, position.y, position.z);
}

void Camera::SetRadius(float planetScale) {
    radius = 5.0f * planetScale;
}

//Rotate camera left or right (x-axis) with A and D keys
void Camera::MoveX(bool right){
    float direction = 1.0f * (right ? 1.0f: -1.0f);
    theta += direction;

    //clamp to handle overflow
    if (theta < 0.0f)
        theta += 360.0f;
    else if (theta > 360.0f)
        theta -= 360.0f;
}

//Rotate camera up or down (y-axis) with R and F keys
void Camera::MoveY(bool up) {
    //bool up: is the movement up or down?
    float direction = 0.5f * (up ? 1.0f : -1.0f);
    phi += direction;

    //clamp to handle overflow
    if (phi < 1.0f)
        phi = 1.0f;
    else if (phi > 180.0f)
        phi = 179.0f;
}

//Zoom the camera in or out (z-axis) with W and S keys
void Camera::MoveZ(bool in) {
    float direction = 0.1f * (in ? 1.0f : -1.0f);
    radius += direction;

    //clamp to prevent view flipping from zooming too close
    if (radius < 0.1f)
        radius = 0.1f;
}

void Camera::ResetAngle() {
    theta = 270.0f;
    phi = 90.0f;
}

//Reset the camera angle so the camera is facing 
//the sunlit side of the planet
void Camera::ResetAngle(glm::vec3 planetLoc) {
    //Since the sun is at (0,0,0), negating the vector lets us
    // get the vector from the sun to the planet for direction
    glm::vec3 view = glm::normalize(-planetLoc);

    theta = atan2(view.z,view.x) * (180.0f / M_PI);
    phi = (acos(view.y / 1.0f) * (180.0f / M_PI)) - 30.0f;
    //the - 20.0f is used to add some perspective
}