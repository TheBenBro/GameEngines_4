#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		//Diffuse
		else if (line.substr(0, 4) == "\tKd ") {
			std::stringstream kd(line.substr(4));

			kd >> m.diffuse.x >> m.diffuse.y >> m.diffuse.z;
			//MaterialHandler::GetInstance()->AddMaterial(m);
		}
		//Ambient
		else if (line.substr(0, 4) == "\tKa ") {
			std::stringstream kd(line.substr(4));

			kd >> m.ambient.x >> m.ambient.y >> m.ambient.z;
			//MaterialHandler::GetInstance()->AddMaterial(m);
		}
		//Specular
		else if (line.substr(0, 4) == "\tKs ") {
			std::stringstream kd(line.substr(4));

			kd >> m.specular.x >> m.specular.y >> m.specular.z;
			//MaterialHandler::GetInstance()->AddMaterial(m);
		}
		//Shininess
		else if (line.substr(0, 4) == "\tNs ") {
			std::stringstream kd(line.substr(4));

			kd >> m.shininess;
			//MaterialHandler::GetInstance()->AddMaterial(m);
		}
		//Transparency
		else if (line.substr(0, 3) == "\td ") {
			std::stringstream kd(line.substr(3));

			kd >> m.transparancy;
			//MaterialHandler::GetInstance()->AddMaterial(m);
		}
	}
	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandle::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0) {
		TextureHandle::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/"
			+ fileName_ + ".png");
		currentTexture = TextureHandle::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
