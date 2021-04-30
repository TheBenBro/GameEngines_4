#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H
#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"
constexpr auto CHILDREN_NUMBER = 8;
enum class OctoChildren {
	OCT_TLF,
	OCT_BLF,
	OCT_BRF,
	OCT_TRF,
	OCT_TLR,
	OCT_BLR,
	OCT_BRR,
	OCT_TRR

};
class OctNode
{
public:
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth);
	OctNode* GetParent();
	OctNode* GetChild(OctoChildren childPos_);
	void AddCollisionObject(GameObject* obj_);
	int GetObjectCount() const;
	bool isLeaf() const;
	BoundingBox* GetBoundingBox()const;
	int GetChildCount() const;
private:
	friend class OctSpatialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	std::vector<GameObject*> objectList;
	float size;
	static int childNum;
};

class OctSpatialPartition {
public:
	OctSpatialPartition(float worldSize_);
	~OctSpatialPartition();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);
private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* obj_);
	void PrepareCollisionQuery(OctNode* cel_, Ray ray_);
};
#endif // !OCTSPATIALPARTITION_H
