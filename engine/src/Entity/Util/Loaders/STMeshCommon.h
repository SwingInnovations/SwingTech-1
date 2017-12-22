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
    STList<STMeshNode*> m_children;
    ~STMeshNode(){
        m_children.clear();
    }
};

#define NUM_BONE_FOR_VERTS 4

/**
 * @brief Bone Weight Information
 */
struct STBoneWeight{
    stUint m_vertexID[NUM_BONE_FOR_VERTS];
    stReal m_weight[NUM_BONE_FOR_VERTS];

    inline void addBoneData(stUint id, stReal weight){
        for(stUint i = 0; i < 4; i++){
            if(m_weight[i] == 0.0f){
                m_vertexID[i] = id;
                m_weight[i] = weight;
                return;
            }
        }
    }
};

struct STBoneData{
    std::string m_name;
    Matrix4f m_offsetMatrix;
    Matrix4f m_finalTransformation;
};

/**
 * @brief Common Mesh Structure
 */
struct STMesh_Structure{
    std::string name;
    std::string materialKey;
    Vector3<stReal> m_minPt;
    Vector3<stReal> m_maxPt;
    stUint m_baseVertex;
    stUint m_baseIndex;
    std::vector<int> m_indices;
    std::vector<Vertex> m_vertices;
    STList<STBoneData*> m_boneData;
    std::map<std::string, stUint> m_boneMap;
    std::vector<STBoneWeight> m_boneWeights;
    STMeshNode* m_node;
    STList<STAnimation*> m_animations;
    bool m_hasAnimations = false;
    bool m_hasBones = false;
    Matrix4f globalInverseMat;

    Vertex* getVertices(){ return &m_vertices[0]; }
    int* getIndicies(){ return &m_indices[0]; }

    inline stInt getVertexSize()const { return (stInt)m_vertices.size(); }
    inline stInt getIndexSize() const { return (stInt)m_indices.size(); }
};

#endif //SWINGTECH1_STMESHCOMMON_H
