#ifndef SWINGTECH1_STMESHCOMMON_H
#define SWINGTECH1_STMESHCOMMON_H

#include <vector>
#include "../../../Application/Util/Data_Structure/STList.h"
#include "../../../Math/STCore.h"
#include "../../../Math/Vector.h"
#include "../../../Math/Vertex.h"
#include "../../../Math/Matrix.h"
#include "STAnimationCommon.h"

struct STMeshNode{
    std::string m_Name;
    Matrix4f transform;
    STMeshNode** m_children;
};

/**
 * @brief Bone Weight Information
 */
struct STBoneWeight{
    stUint m_vertexID;
    stReal m_weight;
};

struct STBoneData{
    std::string m_name;
    STBoneWeight* m_boneWeights;
    Matrix4f m_offsetMatrix;
};

/**
 * @brief Common Mesh Structure
 */
struct STMesh_Structure{
    std::string name;
    std::string materialKey;
    Vector3<stReal> m_minPt;
    Vector3<stReal> m_maxPt;
    std::vector<int> m_indices;
    std::vector<Vertex> m_vertices;
    STBoneData* m_boneData;
    STMeshNode* m_node;
    STList<STAnimation*> m_animations;
    bool m_hasAnimations = false;
    bool m_hasBones = false;

    Vertex* getVertices(){ return &m_vertices[0]; }
    int* getIndicies(){ return &m_indices[0]; }

    inline stInt getVertexSize()const { return (stInt)m_vertices.size(); }
    inline stInt getIndexSize() const { return (stInt)m_indices.size(); }
};

#endif //SWINGTECH1_STMESHCOMMON_H
