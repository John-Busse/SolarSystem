/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "lighting.h"

Lighting::Lighting() {
    //Assimp can't load .mtl files directly, so we have placeholder
    // .obj files to grab the material info
    //start assimp importer
    print = false;

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
    if (print) {
        cout    << materials[mtlIndex].ambient[0] << ", "
                << materials[mtlIndex].ambient[1] << ", "
                << materials[mtlIndex].ambient[2] << ", "
                << materials[mtlIndex].ambient[3] << endl;
    }
    return materials[mtlIndex].ambient;
}

float* Lighting::GetAmbient() {
    static float a[4] = { 0.2473f, 0.1995f, 0.0745f, 1 };
    return (float*)a;
}

float* Lighting::GetDiffuse(int mtlIndex) {
    if (print) {
        cout    << materials[mtlIndex].diffuse[0] << ", "
                << materials[mtlIndex].diffuse[1] << ", "
                << materials[mtlIndex].diffuse[2] << ", "
                << materials[mtlIndex].diffuse[3] << endl;
    }
    return materials[mtlIndex].diffuse;
}

float* Lighting::GetDiffuse() {
    static float a[4] = { 0.7516f, 0.6065f, 0.2265f, 1 }; 
    return (float*)a;
}

float* Lighting::GetSpecular(int mtlIndex) {
    if (print) {
        cout    << materials[mtlIndex].specular[0] << ", "
                << materials[mtlIndex].specular[1] << ", "
                << materials[mtlIndex].specular[2] << ", "
                << materials[mtlIndex].specular[3] << endl;
    }
    return materials[mtlIndex].specular;
}

float* Lighting::GetSpecular() { 
    static float a[4] = { 0.6283f, 0.5558f, 0.3661f, 1 };
    return (float*)a; 
}

float Lighting::GetShine(int mtlIndex) {
    if (print) {
        cout << "shine is " << materials[mtlIndex].shine << endl;
        cout << "index is " << mtlIndex << endl << endl;
        print = !(mtlIndex == 9);
    }
    return materials[mtlIndex].shine;
}

float Lighting::GetShine() { 
    return 51.2f; 
}