/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef SHADER_H
#define SHADER_H

#include "glHeaders.h"

class Shader {
    public:
        Shader();
        Shader(const char *vertFile, const char *fragFile);
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

        //GLuint CreateShaderProgram();
        string ReadShaderSource(const char*);

        //error handling
        void PrintShaderLog(GLuint* shaderInfo);
        void PrintProgramLog();
        bool CheckOpenGLError();

    private:
        GLuint shaderProg;
        vector<GLuint> shaderObjList;
};
#endif