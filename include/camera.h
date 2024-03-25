/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef CAMERA_H
#define CAMERA_H

#include "glHeaders.h"

class Camera {
    public:
        Camera();
        Camera(int &width, int &height);
        ~Camera();

        glm::vec3 GetCamPos();
        glm::vec3 GetFocus();
        glm::mat4 GetView();
        glm::mat4 GetProj();

        //camera Change functions
        void SetView();
        void SetPos(glm::vec4 position);
        void SetRadius(float planetScale);
        void MoveX(bool right);
        void MoveY(bool up);
        void MoveZ(bool in, float scale);
        void ResetAngle();
        void ResetAngle(glm::vec3 planetLoc);

    private:
        glm::vec3 camPos;
        glm::vec3 focusPos;

        glm::mat4 projection;

        const glm::vec3 UPAXIS = glm::vec3(0.0, 1.0, 0.0);

        float radius, theta, phi;
};
#endif