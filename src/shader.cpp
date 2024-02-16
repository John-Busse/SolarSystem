/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "shader.h"

Shader::Shader() {
    shaderProg = glCreateProgram();

    if (shaderProg == 0) {
        throw "Error creating shader program";
    }
}

Shader::~Shader() {
    for (vector<GLuint>::iterator it = shaderObjList.begin(); it != shaderObjList.end() ; it++ ) {
        glDeleteShader(*it);        
    }
    shaderObjList.clear();

    if (shaderProg != 0) {
        glDeleteProgram(shaderProg);
        shaderProg = 0;
    }
}

void Shader::Enable() {
    glUseProgram(shaderProg);
}

bool Shader::AddShader(GLenum shaderType, const char* filename) {
    GLuint shaderObj = glCreateShader(shaderType);
    GLint errorHandler;

    if (shaderObj == 0) {
        cerr << "Error creating shader type " << shaderType << endl;
        return false;
    }

    shaderObjList.push_back(shaderObj);

    string shaderStr = ReadShaderSource(filename);

    if(shaderStr == "") {
        cerr << "file " << filename << "read error" << endl;
        return false;
    }

    const GLchar *shaderSource = shaderStr.c_str();

    glShaderSource(shaderObj, 1, &shaderSource, NULL);

    //compile the shader
    glCompileShader(shaderObj);
    CheckOpenGLError();
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &errorHandler);

    if(errorHandler != 1) {
        cerr << "shader compilation failure of " << filename << endl;
        PrintShaderLog(&shaderObj);
    }

    glAttachShader(shaderProg, shaderObj);

    return true;
}

bool Shader::Finalize() {
    GLint errorHandler;

    glLinkProgram(shaderProg);
    CheckOpenGLError();
    glGetProgramiv(shaderProg, GL_LINK_STATUS, &errorHandler);

    if (errorHandler != 1) {
        cerr << "linking failed" << endl;
        PrintProgramLog();
        return false;
    }

    glValidateProgram(shaderProg);
    glGetProgramiv(shaderProg, GL_VALIDATE_STATUS, &errorHandler);
    if (errorHandler != 1) {
        cerr << "validation falied" << endl;
        PrintProgramLog();
        return false;
    }

    // delete intermediate shader objects
    for (vector<GLuint>::iterator it = shaderObjList.begin(); it != shaderObjList.end(); it++) {
        glDeleteShader(*it);
    }

    return true;
}

string Shader::ReadShaderSource(const char *filePath) {
    string content;
    ifstream inFile;
    string line = "";
    inFile.open(filePath, ios::in);

    if (!inFile) {
        cerr << "file " << filePath << " not found." << endl;
        return line;
    }

    while (!inFile.eof()) {
        getline(inFile, line);
        content.append(line + "\n");
    }
    inFile.close();
    return content;
}

GLint Shader::GetUniformLoc(const char* uniformName) {
    GLint location = glGetUniformLocation(shaderProg, uniformName);

    if (location == GL_INVALID_VALUE) {
        cerr << "Error: Unable to get location of " << uniformName << endl;
    }

    return location;
}

void Shader::PrintShaderLog(GLuint *shader) {
    int len = 0;
    int chWritten = 0;
    char *log;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetShaderInfoLog(*shader, len, &chWritten, log);
        cerr << "Shader Info Log: " << log << endl;
        free(log);  //deallocate log
    }
}

void Shader::PrintProgramLog() {
    int len = 0;
    int chWritten = 0;
    char* log;
    glGetProgramiv(shaderProg, GL_INFO_LOG_LENGTH, &len);
    if (len > 0) {
        log = (char*)malloc(len);
        glGetProgramInfoLog(shaderProg, len, &chWritten, log);
        cerr << "Program Info Log: " << log << endl;
        free (log); //deallocate log
    }
}

bool Shader::CheckOpenGLError() {
    bool foundError = false;
    int glErr = glGetError();
    while (glErr != GL_NO_ERROR) {
        cerr << "glError: " << glErr << endl;
        foundError = true;
        glErr = glGetError();
    }

    return foundError;
}