#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), textureCoords(std::vector<glm::vec2>()),
indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentTexture(0)
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;		vert.position = vertices[indices[i-1]];
		vert.normal = normals[normalIndices[i-1]];
		vert.textureCoordinates = textureCoords[textureIndices[i-1]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.textureID = currentTexture;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentTexture = 0;
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 2) == "v ") {

			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}

		if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(3));

			float x, y, z;
			vt >> x >> y >> z;
			textureCoords.push_back(glm::vec2(x, y));
		}

		if (line.substr(0, 3) == "vn ") {
			std::stringstream vn(line.substr(3));
			float x, y, z;

			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		if (line.substr(0, 2) == "f ") {
			std::stringstream vn(line.substr(2));
			vn.ignore(line.length(), '/');
			int x, y, z;
			vn >> x >> y >> z;
			indices.push_back(x);
			textureIndices.push_back(y);
			normalIndices.push_back(z);
		}

		else if (line.substr(0, 7) == "usemt1 ") {

			if (indices.size() > 0) {
				PostProcessing();

			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentTexture = TextureHandle::GetInstance()->GetTexture(matName_);
	if (currentTexture == 0) {
		TextureHandle::GetInstance()->CreateTexture(matName_, "Resources/Textures/" + matName_ + ".png");
		currentTexture = TextureHandle::GetInstance()->GetTexture(matName_);
	}
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	std::ifstream in(matFilePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl	") {
			LoadMaterial(line.substr(7));
		}
	}
}
