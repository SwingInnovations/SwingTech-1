#ifndef SWINGTECH_VKMESH_H
#define SWINGTECH_VKMESH_H

#include <vulkan/vulkan.h>
#include "../../Entity/Util/STMesh.h"

class VKMesh : public STMesh {
public:
	VKMesh(STMesh_Structure structure);
	void load(std::ifstream& in, bool hasBones) override;
	void draw() override;
private:
	enum {
		VERTEX_ATTRIB,
		TEXCOORD_ATTRIB,
		NORMAL_ATTRIB,
		INDEX_ATTRIB,
		TANGENT_ATTRIB,
		BITANGENT_ATTRIB,
		NUM_ATTRIBS
	};

	VkVertexInputAttributeDescription m_attributes[NUM_ATTRIBS];
};

#endif