/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef SHADER_H
#define SHADER_H

#include "glHeaders.h"
#include "lighting.h"

class Shader {
    public:
        Shader();
        ~Shader();

        //Shader Compiling
        void Enable();
        bool AddShader(GLenum shaderType, const char* fileName);
        bool Finalize();

        //Render functions
        GLint GetUniformLoc(const char* UniformName);
        void SetProg4fv(GLuint shaderLoc, float* values);
        void SetProg3fv(GLuint shaderLoc, float* values);
        void SetProg1f(GLuint shaderLoc, float value);
        void InstallLights(glm::mat4 vMatrix, int matIndex);

        //GLuint CreateShaderProgram();
        string ReadShaderSource(const char*);

        //error handling
        void PrintShaderLog(GLuint* shaderInfo);
        void PrintProgramLog();
        bool CheckOpenGLError();

    private:
        //finalization helper
        void FindValues();

        GLuint shaderProg;
        vector<GLuint> shaderObjList;
        Lighting* glLighting;

        //shader variables
        GLuint globalAmbLoc, 
         ambLoc, diffLoc, specLoc, posLoc, 
         mAmbLoc, mDiffLoc, mSpecLoc, mShiLoc;

        //lighting variables
        glm::vec3 lightPosV, initialLightLoc = glm::vec3(0.0f, 0.0f, 0.0f);
        float lightPos[3];

        //white light properties
        float globalAmbient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
        float lightAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
        float lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        float lightSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
};
#endif