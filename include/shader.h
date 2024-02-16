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
        ~Shader();

        void Enable();
        bool AddShader(GLenum, const char*);
        bool Finalize();
        GLint GetUniformLoc(const char* UniformName);

        //GLuint CreateShaderProgram();
        string ReadShaderSource(const char*);

        //error handling
        void PrintShaderLog(GLuint*);
        void PrintProgramLog();
        bool CheckOpenGLError();

    private:
        GLuint shaderProg;
        vector<GLuint> shaderObjList;
};
#endif