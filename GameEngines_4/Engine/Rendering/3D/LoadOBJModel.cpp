#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), textureCoords(std::vector<glm::vec2>()),
indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()),
meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material()), maxX(0), maxY(0), maxZ(0), minX(0), minY(0), minZ(0)
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

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size();i++) {
		Vertex vert;		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
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
			
			if (maxX == 0.0f || maxX < x) {
				maxX = x;
				boundingBox.maxVert.x = maxX;
			}
			if (maxY == 0.0f || maxY < y) {
				maxY = y;
				boundingBox.maxVert.y = maxY;
			}
			if (maxZ == 0.0f || maxZ < z) {
				maxZ = z;
				boundingBox.maxVert.z = maxZ;
			}
			
			if (minX == 0.0f || minX > x) {
				minX = x;
				boundingBox.minVert.x = minX;
			}
			if (minY == 0.0f || minY > y) {
				minY = y;
				boundingBox.minVert.y = minY;
			}
			if (minZ == 0.0f || minZ > z) {
				minZ = z;
				boundingBox.minVert.z = minZ;
			}
			vertices.push_back(glm::vec3(x, y, z));
			
		}

		else if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(3));

			GLfloat x, y, z;
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
			char dummy;
			unsigned int a, b, c, aT, bT, cT, aN, bN, cN;
			vn >> a >> dummy >> aT >> dummy >> aN >> b >> dummy >> bT >> dummy >> bN
				>> c >> dummy >> cT >> dummy >> cN;

			a--; b--; c--;
			aT--; bT--; cT--;
			aN--; bN--; cN--;

			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);

			normalIndices.push_back(aN);
			normalIndices.push_back(bN);
			normalIndices.push_back(cN);

			textureIndices.push_back(aT);
			textureIndices.push_back(bT);
			textureIndices.push_back(cT);
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
