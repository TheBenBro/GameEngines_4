#include "MaterialHandler.h"

MaterialHandler* MaterialHandler::GetInstance()
{
    if (materialInstance.get() == nullptr) {
        materialInstance.reset(new MaterialHandler);
    }
    return materialInstance.get();
}

void MaterialHandler::AddMaterial(Material mat_)
{
    materials.push_back(mat_);
}

Material MaterialHandler::GetMaterial(const std::string& matName) const
{
    for (auto mat : materials) {
        if (mat.name == matName) {
            return mat;
        }
    }
    return Material();
}

void MaterialHandler::OnDestroy()
{
    if (materials.size() > 0) {
        materials.clear();
    }
}


MaterialHandler::MaterialHandler()
{
    materials.reserve(10);
}

MaterialHandler::~MaterialHandler()
{
    OnDestroy();
}
