/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "shader.h"

Shader::Shader() {
    shaderProg = glCreateProgram();

    if (shaderProg == 0) {
        string err = "Error creating shader program";
        throw err;
    }

    // load the material data
    try {
        glLighting = new Lighting();
    } catch (string err) {
        throw err;
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

    try {
        FindValues();
    } catch (string err) {
        cerr << err << endl;
        return false;
    }

    return true;
}

//Locate the matrices in the shader program
void Shader::FindValues() {
    string err;
    GLuint tester;

    tester = GetUniformLoc("mv_matrix");
    if (tester == GL_INVALID_VALUE) {
        err = "model-view matrix not found in shader";
        throw err;
    }

    tester = GetUniformLoc("proj_matrix");
    if (tester == GL_INVALID_VALUE) {
        err = "proj matrix not found in shader";
        throw err;
    }

    tester = GetUniformLoc("norm_matrix");
    if (tester == GL_INVALID_VALUE) {
        err = "normal matrix not found in shader";
        throw err;
    }

    globalAmbLoc = GetUniformLoc("globalAmbient");
    if (globalAmbLoc == GL_INVALID_VALUE) {
        err = "global ambient vector not found in shader";
        throw err;
    }

    ambLoc = GetUniformLoc("light.ambient");
    if (ambLoc == GL_INVALID_VALUE) {
        err = "positional ambient vector not found in shader";
        throw err;
    }

    diffLoc = GetUniformLoc("light.diffuse");
    if (diffLoc == GL_INVALID_VALUE) {
        err = "positional diffuse vector not found in shader";
        throw err;
    }

    specLoc = GetUniformLoc("light.specular");
    if (specLoc == GL_INVALID_VALUE) {
        err = "positional specular vector not found in shader";
        throw err;
    }

    posLoc = GetUniformLoc("light.position");
    if (posLoc == GL_INVALID_VALUE) {
        err = "positional vector not found in shader";
        throw err;
    }

    mAmbLoc = GetUniformLoc("material.ambient");
    if (mAmbLoc == GL_INVALID_VALUE) {
        err = "material ambient vector not found in shader";
        throw err;
    }

    mDiffLoc = GetUniformLoc("material.diffuse");
    if (mDiffLoc == GL_INVALID_VALUE) {
        err = "material diffuse vector not found in shader";
        throw err;
    }

    mSpecLoc = GetUniformLoc("material.specular");
    if (mSpecLoc == GL_INVALID_VALUE) {
        err = "material specular vector not found in shader";
        throw err;
    }

    mShiLoc = GetUniformLoc("material.shine");
    if (mShiLoc == GL_INVALID_VALUE) {
        err = "material shine value not found in shader";
        throw err;
    }
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

void Shader::SetProg4fv(GLuint shaderLoc, float* values) {
    glProgramUniform4fv(shaderProg, shaderLoc, 1, values);
}

void Shader::SetProg3fv(GLuint shaderLoc, float* values) {
    glProgramUniform3fv(shaderProg, shaderLoc, 1, values);
}

void Shader::SetProg1f(GLuint shaderLoc, float value) {
    glProgramUniform1f(shaderProg, shaderLoc, value);
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

void Shader::InstallLights(glm::mat4 vMatrix, int matIndex) {
    lightPosV = glm::vec3(vMatrix * glm::vec4(initialLightLoc, 1.0f));
    lightPos[0] = lightPosV.x;
    lightPos[1] = lightPosV.y;
    lightPos[2] = lightPosV.z;
    
    //get light/material field locations in the shader
    globalAmbLoc = GetUniformLoc("globalAmbient");
    ambLoc = GetUniformLoc("light.ambient");
    diffLoc = GetUniformLoc("light.diffuse");
    specLoc = GetUniformLoc("light.specular");
    posLoc = GetUniformLoc("light.position");
    mAmbLoc = GetUniformLoc("material.ambient");
    mDiffLoc = GetUniformLoc("material.diffuse");
    mSpecLoc = GetUniformLoc("material.specular");
    mShiLoc = GetUniformLoc("material.shine");

    //Set uniform light/material values in shader
    SetProg4fv(globalAmbLoc, globalAmbient);
    SetProg4fv(ambLoc, lightAmbient);
    SetProg4fv(diffLoc, lightDiffuse);
    SetProg4fv(specLoc, lightSpecular);
    SetProg3fv(posLoc, lightPos);
    SetProg4fv(mAmbLoc, glLighting->GetAmbient(matIndex));
    SetProg4fv(mDiffLoc, glLighting->GetDiffuse(matIndex));
    SetProg4fv(mSpecLoc, glLighting->GetSpecular(matIndex));
    SetProg1f(mShiLoc, glLighting->GetShine(matIndex));
}
