/* John Busse jbusse@nevada.unr.edu
Computer Graphics Programming; openGL with C++
Solar System Project
*/
#include "object.h"

Object::Object() {

}

Object::Object(GLuint* vao, GLuint* vbo, GLuint* ibo) {
	string err;
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);
	glGenBuffers(numVBOs, ibo);

	//start assimp importer
	Assimp::Importer importer;

	//in this function, we're loading the objects into the buffers
	for (int i = 0; i < numVBOs;  i++) {
		const aiScene* scene = importer.ReadFile(OBJFILES[i].c_str(), aiProcess_Triangulate);

		if (!scene) {
			err = "importer.ReadFile(" + OBJFILES[i] + ") error: " + importer.GetErrorString();
			throw err;
		}

		if (!scene->HasMeshes()) {
			err = "scene " + OBJFILES[i] + " has no meshes";
			throw err;
		}

		if (LoadOBJ(scene) == -1) {
			err = "mesh has either no positions or no faces";
			throw err;
		}

		//load the vertex and index info into the array buffers
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices[i].size(), &vertices[i][0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices[i].size(), &indices[i][0], GL_STATIC_DRAW);
	}
}

Object::~Object() {
}

int Object::LoadOBJ(const aiScene* scene) {
	//since we're using simple .obj files, they only have 1 Mesh, at index 0
	//a more robust code may be used later for larger objects/scenes
	aiMesh &mesh = *scene->mMeshes[0];
	vector<Vertex> vertBuffer;
	glm::vec3 tempVertex;
	glm::vec2 tempUV;
	vector<unsigned int> indBuffer;

	if (!mesh.HasPositions() || !mesh.HasFaces())
		return -1;

	//if we were using the material in the obj file, we'd pull that data here

	//for each face in the mesh...
	for (int i = 0; i < mesh.mNumFaces; i++) {
		aiFace face = mesh.mFaces[i];

		for (int j = 0; j < 3; j++) {
			//enter the faces
			indBuffer.push_back(face.mIndices[j]);

			//enter the vertex/UV
			glm::vec3 thisVertex = ConvertVec3(mesh.mVertices[face.mIndices[j]]);
			glm::vec2 thisUV = ConvertVec2(mesh.mTextureCoords[0][face.mIndices[j]]);
			Vertex *temp = new Vertex(thisVertex, thisUV);
			vertBuffer.push_back(*temp);
		}
	}
	vertices.push_back(vertBuffer);
	indices.push_back(indBuffer);

	return 0;
}

int Object::GetFaces(int index) {
	return  indices[index].size();
}

glm::vec3 Object::ConvertVec3(aiVector3D inVector) {
	return glm::vec3(inVector.x, inVector.y, inVector.z);
}

glm::vec2 Object::ConvertVec2(aiVector3D inVector) {
	return glm::vec2(inVector.x, inVector.y);
}