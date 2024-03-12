/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#ifndef OBJECT_H
#define OBJECT_H

#include "glHeaders.h"

class Object {
    public:
        Object();
        Object(GLuint* vao, GLuint* vbo, GLuint* ibo, GLuint* nbo);
        Object(char* fileName, int index);
        ~Object();

        float* GetVertices();
        int GetFaces(int id);
        int LoadOBJ(const aiScene* scene);

    private:
        //helper functions
        glm::vec3 ConvertVec3(aiVector3D inVec);
        glm::vec2 ConvertVec2(aiVector3D inVec);

        const string OBJFILES[3] = 
        {"../models/sphere.obj", 
        "../models/SaturnRing.obj", 
        "../models/smallring.obj"};
        unsigned int  faces[1];
        vector<vector<Vertex>> vertices;
        vector<vector<unsigned int>> indices;
        vector<vector<glm::vec3>> normals;
};
#endif