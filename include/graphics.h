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
        bool Init(int& w, int& h);
        void Render(float deltaTime);

        //camera functions
        void CameraMoveX(bool right);
        void CameraMoveY(bool up);
        void CameraMoveZ(bool in);
        void ResetAngle();

        //simulation functions
        void SetPlanet(int planet);
        void ChangeSpeed(bool faster);

    private:
        //Setup functions
        void SetupShaders();
        void FindLighting();

        //Render functions
        void MatStack(int numMoons, float deltaTime);
        void Draw(Planet thisPlanet);

        //Debug functions
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

        //shader variables
        //char *unlitVert, *unlitFrag, *bpVert, *bpFrag;
        char *vert, *frag;
        GLuint projLoc, mvLoc, nLoc; //local mvp matrix vars
        glm::mat4 pMat, vMat, mMat, mvMat, invTraMat;

        //render variables
        float timeScale;
        GLuint vao[numMesh];
        GLuint vbo[numMesh];
        GLuint ibo[numMesh];
        GLuint nbo[numMesh];
        GLuint thisTexture;

        //Camera variables
        int planetIndex;
        bool updateCamera;
};
#endif