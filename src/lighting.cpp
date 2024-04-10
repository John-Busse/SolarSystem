/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "lighting.h"

Lighting::Lighting() {
    //Assimp can't load .mtl files directly, so we have placeholder
    // .obj files to grab the material info
    //start assimp importer
    Assimp::Importer importer;
    aiColor3D colorVals;
    float opacity;

    for (int i = 0; i < numObj; i++) {
        const aiScene* scene = importer.ReadFile(MTLFILES[i].c_str(), aiProcess_Triangulate);

        if (!scene) {
            string err = "importer.ReadFile(" + MTLFILES[i] + ") error: " + importer.GetErrorString();
            throw err;
        }

        // grab the material
        aiMaterial *mtl = scene->mMaterials[1];

        aiString name = mtl->GetName();

        // grab and enter the color values
        mtl->Get(AI_MATKEY_OPACITY, opacity);
        
        mtl->Get(AI_MATKEY_COLOR_AMBIENT, colorVals);
        float tempAmb[] = {colorVals.r, colorVals.g, colorVals.b, opacity};

        mtl->Get(AI_MATKEY_COLOR_DIFFUSE, colorVals);
        float tempDiff[] = {colorVals.r, colorVals.g, colorVals.b, opacity};

        mtl->Get(AI_MATKEY_COLOR_SPECULAR, colorVals);
        float tempSpec[] = {colorVals.r, colorVals.g, colorVals.b, opacity};

        mtl->Get(AI_MATKEY_COLOR_TRANSPARENT, colorVals);

        for (int j = 0; j < 4; j++) {
            materials[i].ambient[j] = tempAmb[j];
            materials[i].diffuse[j] = tempDiff[j];
            materials[i].specular[j] = tempSpec[j];
        }

        mtl->Get(AI_MATKEY_SHININESS, materials[i].shine);
    }
}

Lighting::~Lighting() {

}

float* Lighting::GetAmbient(int mtlIndex) {
    return materials[mtlIndex].ambient;
}

float* Lighting::GetAmbient() {
    static float a[4] = { 0.2473f, 0.1995f, 0.0745f, 1 };
    return (float*)a;
}

float* Lighting::GetDiffuse(int mtlIndex) {
    return materials[mtlIndex].diffuse;
}

float* Lighting::GetDiffuse() {
    static float a[4] = { 0.7516f, 0.6065f, 0.2265f, 1 }; 
    return (float*)a;
}

float* Lighting::GetSpecular(int mtlIndex) {
    return materials[mtlIndex].specular;
}

float* Lighting::GetSpecular() { 
    static float a[4] = { 0.6283f, 0.5558f, 0.3661f, 1 };
    return (float*)a; 
}

float Lighting::GetShine(int mtlIndex) {
    return materials[mtlIndex].shine;
}

float Lighting::GetShine() { 
    return 51.2f; 
}

void Lighting::InstallLights(glm::mat4 vMatrix, int matIndex, Shader *thisShader) {
    lightPosV = glm::vec3(vMatrix * glm::vec4(lightLoc, 1.0f));
    lightPos[0] = lightPosV.x;
    lightPos[1] = lightPosV.y;
    lightPos[2] = lightPosV.z;
    
    //get light/material field locations in the shader
    globalAmbLoc = thisShader->GetUniformLoc("globalAmbient");
    ambLoc = thisShader->GetUniformLoc("light.ambient");
    diffLoc = thisShader->GetUniformLoc("light.diffuse");
    specLoc = thisShader->GetUniformLoc("light.specular");
    posLoc = thisShader->GetUniformLoc("light.position");
    mAmbLoc = thisShader->GetUniformLoc("material.ambient");
    mDiffLoc = thisShader->GetUniformLoc("material.diffuse");
    mSpecLoc = thisShader->GetUniformLoc("material.specular");
    mShiLoc = thisShader->GetUniformLoc("material.shine");

    //Set uniform light/material values in shader
    thisShader->SetProg4fv(globalAmbLoc, globalAmbient);
    thisShader->SetProg4fv(ambLoc, lightAmbient);
    thisShader->SetProg4fv(diffLoc, lightDiffuse);
    thisShader->SetProg4fv(specLoc, lightSpecular);
    thisShader->SetProg3fv(posLoc, lightPos);
    thisShader->SetProg4fv(mAmbLoc, GetAmbient(matIndex));
    thisShader->SetProg4fv(mDiffLoc, GetDiffuse(matIndex));
    thisShader->SetProg4fv(mSpecLoc, GetSpecular(matIndex));
    thisShader->SetProg1f(mShiLoc, GetShine(matIndex));
}