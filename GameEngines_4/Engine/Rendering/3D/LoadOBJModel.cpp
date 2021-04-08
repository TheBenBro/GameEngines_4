#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), textureCoords(std::vector<glm::vec2>()),
indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material())
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
	for (unsigned int i = 0; i < indices.size();i++) {
		Vertex vert;		vert.position = vertices[indices[i]-1];
		vert.normal = normals[normalIndices[i]-1];
		vert.textureCoordinates = textureCoords[textureIndices[i]-1];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
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

		else if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(3));

			float x, y, z;
			vt >> x >> y >> z;
			textureCoords.push_back(glm::vec2(x, y));
		}

		else if (line.substr(0, 3) == "vn ") 
		{
			std::stringstream vn(line.substr(3));
			float x, y, z;

			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		else if (line.substr(0, 2) == "f ") 
		{
			std::stringstream vn(line.substr(2));
			GLint tmp = 0;
			int counter = 0;
			while (vn >> tmp) {
				if (counter == 0)
					indices.push_back(tmp);
				else if (counter == 1)
					textureIndices.push_back(tmp);
				else if (counter == 2)
					normalIndices.push_back(tmp);
				if (vn.peek() == '/') {
					++counter;
					vn.ignore(1, '/');
				}
				else if (vn.peek() == ' ') {
					++counter; 
					vn.ignore(1, ' ');
				}
				if (counter > 2) {
					counter = 0;
				}
			}
		}

		else if (line.substr(0, 7) == "usemtl ") {

			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
	in.close();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
