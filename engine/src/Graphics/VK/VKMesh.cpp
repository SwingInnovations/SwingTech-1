#include "VKMesh.h"

VKMesh::VKMesh(STMesh_Structure structure) {
	m_attributes[0] = VkVertexInputAttributeDescription();
	m_attributes[0].binding = 0;
	m_attributes[0].location = 0;
	m_attributes[0].format = VK_FORMAT_R32G32B32_SFLOAT;
}