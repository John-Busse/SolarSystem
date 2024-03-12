/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "graphics.h"

Graphics::Graphics() {

}

Graphics::Graphics(vector<Planet>& newPlanetInfo) {
    planetInfo = &newPlanetInfo;
    timeScale = 0.01f;
    planetIndex = 0;
    updateCamera = true;

    //unlitVert = const_cast<char*>("shaders/unlitVert.glsl");
    //unlitFrag = const_cast<char*>("shaders/unlitFrag.glsl");
    //bpVert = const_cast<char*>("shaders/blinnVert.glsl");
    //bpVert = const_cast<char*>("shaders/blinnVert.glsl");
    vert = const_cast<char*>("shaders/blinnVert.glsl");
    frag = const_cast<char*>("shaders/blinnFrag.glsl");
}

Graphics::~Graphics() {
    delete glCamera;
    glCamera = NULL;
    delete glShader;
    glShader = NULL;
    delete glObject;
    glObject = NULL;
    delete glTexture;
    glTexture = NULL;
    delete glInterface;
    glInterface = NULL;

    delete vert;
    vert = NULL;
    delete frag;
    frag = NULL;
}

bool Graphics::Init(int &width, int &height) { //char* infoFile
    //initialize glew
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cerr << "glew failed to initialize: " << glewGetErrorString(err) << endl;
        return false;
    }

    try {
        glCamera = new Camera(width, height);
    } catch (string err) {
        cerr << err << endl;
        return false;
    }

    //Create object(s)
    try{
        glObject = new Object(vao, vbo, ibo, nbo);
    }
    catch (string err) {
        cerr << err << endl;
        return false;
    }

    //set up textures
    try {
        glTexture = new Texture();
    }
    catch(string err) {
        cerr << err << endl;
        return false;
    }

    //set up shaders
    try {
        SetupShaders();
    } catch (string err) {
        cerr << err << endl;
        return false;
    }

    //set up user interface
    try {
        glInterface = new Interface();
    } catch (string err) {
        cerr << err << endl;
        return false;
    }

    //initial OpenGL options
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
}

void Graphics::SetupShaders() {
    //set up 
    try {
    glShader = new Shader();
    } catch (string err) {
        throw err;
    }

    //Add blinn-phong shader
    if (!glShader->AddShader(GL_VERTEX_SHADER, vert)) {
        string err = "vertex shader failed";
        throw err;
    }

    if (!glShader->AddShader(GL_FRAGMENT_SHADER, frag)) {
        string err = "fragment shader failed";
        throw err;
    }

    if (!glShader->Finalize()) {
        string err = "shader failed to initialize\n";
        throw err;
    }
}

void Graphics::Render(float deltaTime) {
    //clear the screen
    glClearColor(0.01f, 0.01f, 0.01f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE); //back face culling

    //start the shader
    glShader->Enable();

    //get uniform variables for MVP Matrices
    mvLoc = glShader->GetUniformLoc("mv_matrix");
    projLoc = glShader->GetUniformLoc("proj_matrix");
    nLoc = glShader->GetUniformLoc("norm_matrix");

    //build mvp matrices
    mStack.push(glm::mat4(1.0f));     //Push mat0: identity matrix
    vMat = glCamera->GetView();
    pMat = glCamera->GetProj();

    stackPos = 0;
    MatStack(1, deltaTime);

    //clear the Matrix stack
    while(!mStack.empty()) {
        mStack.pop();
    }
}

void Graphics::MatStack(int numMoons, float deltaTime) {
    for (int i = 0; i < numMoons; i++) {
        Planet thisPlanet = (*planetInfo)[stackPos];
        mStack.push(mStack.top());    //push copy of previous matrix

        //incrememnt the orbit angle with dt
        thisPlanet.orbitAngle += deltaTime * thisPlanet.orbitSpeed * timeScale;
        //prevent overflow issues
        if (thisPlanet.orbitAngle > (glm::pi<float>() * 2.0f)) {
            thisPlanet.orbitAngle -= (glm::pi<float>() * 2.0f);
        }

        //rotate for orbital inclination
        mStack.top() *= glm::rotate(glm::mat4(1.0f), thisPlanet.orbitTilt, glm::vec3(0.0f, 0.0f, 1.0f));

        //translate for orbit rotation
        mStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(
            sin(thisPlanet.orbitAngle) * thisPlanet.orbitDistance,
            0.0f,
            cos(thisPlanet.orbitAngle) * thisPlanet.orbitDistance));

        mStack.push(mStack.top());    //copy position matrix for rotation/scale

        //move camera to current planet
        if (thisPlanet.texIndex == planetIndex) {
            // the third column of the matrix holds position information
            glCamera->SetPos(mStack.top()[3]);
            if (updateCamera) {
                glCamera->SetRadius(thisPlanet.planetScale);
                if (planetIndex == 0) {
                    //Reset to the default
                    glCamera->ResetAngle();
                } else {
                    //Overloaded reset angle sets the camera
                    // to face the sunlit side of the planet
                    glCamera->ResetAngle(mStack.top()[3]);
                }
                updateCamera = false;
            }
        }

        thisPlanet.rotateAngle += deltaTime * thisPlanet.rotateSpeed * timeScale * 100.0f;
        //prevent overflow issues
        if (thisPlanet.rotateAngle > (glm::pi<float>() * 2.0f)) {
            thisPlanet.rotateAngle -= (glm::pi<float>() * 2.0f);
        }

        //spin planet
        mStack.top() *= glm::rotate(glm::mat4(1.0f), thisPlanet.rotateAngle, glm::vec3(0.0f, 1.0f, 0.0f));
        //set scale
        mStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(thisPlanet.planetScale, thisPlanet.planetScale, thisPlanet.planetScale));

        Draw(thisPlanet);
        
        mStack.pop();   //pop the rotation/scale matrix

        //update rotation and orbit angles
        (*planetInfo)[stackPos].orbitAngle = thisPlanet.orbitAngle;
        (*planetInfo)[stackPos].rotateAngle = thisPlanet.rotateAngle;
        stackPos++;

        if (thisPlanet.numMoons > 0) {  //if this planet has any moons
            MatStack(thisPlanet.numMoons, deltaTime);
        }
        mStack.pop();   //pop the position matrix
    }
}

void Graphics::Draw(Planet thisPlanet) {
    glShader->InstallLights(vMat, thisPlanet.texIndex);

    //build the MV matrix
    mvMat = vMat * mStack.top();

    //build the inverse transpose of MV matrix, for normal transforms
    invTraMat = glm::transpose(glm::inverse(mvMat));

    //load the MVP matrices into the shader
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTraMat));

    //bind the VAO
    glBindVertexArray(vao[thisPlanet.objIndex]);
    
    //load the vertices into the shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[thisPlanet.objIndex]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(0);

    //load the uvs into the shader
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texture));
    glEnableVertexAttribArray(1);

    //load the normals into the shader
    glBindBuffer(GL_ARRAY_BUFFER, nbo[thisPlanet.objIndex]);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    //bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, glTexture->GetTexture(thisPlanet.texIndex));

    //mipmapping/antialiasing
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    //anisotropic filtering (if supported)
    if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
        GLfloat anisoSetting = 0.0f;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);        
    }

    glEnable(GL_LEQUAL);
    //glFrontFace(GL_CCW);

    //Draw the object
    glDrawElements(GL_TRIANGLES, glObject->GetFaces(thisPlanet.objIndex), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Graphics::ChangeSpeed(bool faster) {
    timeScale += (faster ? 0.01f : -0.01f); //increment timescale

    if (timeScale < 0.0f) { //if the timescale is less than 0.0, clamp it
        timeScale = 0.0f;
    } else if (timeScale > 0.2f) {  //if the timescale is greater than the max, clamp it
        timeScale = 0.2f;
    }
}

void Graphics::SetPlanet(int index) {
    planetIndex = index;
    updateCamera = true;
}

void Graphics::CameraMoveX(bool right){
    glCamera->MoveX(right);
}

void Graphics::CameraMoveY(bool up) {
    glCamera->MoveY(up);
}

void Graphics::CameraMoveZ(bool in) {
    glCamera->MoveZ(in);
}

void Graphics::ResetAngle() {
    glCamera->ResetAngle();
}