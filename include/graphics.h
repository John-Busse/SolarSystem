/*John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "glHeaders.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "texture.h"
#include "interface.h"

class Graphics {
    public:
        Graphics();
        Graphics(vector<Planet>& planetInfo);
        ~Graphics();
        bool Init(int& w, int& h, char* v, char* f);
        void SetupShaders(char* vFile, char* fFile);
        void Render(float deltaTime);
        void MatStack(int numMoons, float deltaTime);

        void Draw(Planet thisPlanet);
        void ChangeSpeed(bool faster);

        //camera functions
        void SetPlanet(int planet);
        void CameraMoveX(bool right);
        void CameraMoveY(bool up);
        void CameraMoveZ(bool in);
        void ResetAngle();

    private:
        string ErrorString(GLenum*);

        Camera *glCamera;
        Shader *glShader;
        Object *glObject;
        Texture *glTexture;
        Interface *glInterface;

        //matrix stack
        stack<glm::mat4> mStack;
        vector<Planet>* planetInfo;
        int stackPos;

        //render variables
        float timeScale;
        GLuint projLoc, vLoc, mLoc; //local mvp matrix vars
        glm::mat4 pMat, vMat, mMat, mvMat, oMat;
        GLuint vao[numVAOs];
        GLuint vbo[numVBOs];
        GLuint ibo[numVBOs];
        GLuint thisTexture;

        //Camera variables
        int planetIndex;
        bool updateRadius;
};
#endif