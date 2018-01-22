#ifndef SWINGTECH1_STMESHCOMMON_H
#define SWINGTECH1_STMESHCOMMON_H

#include <vector>

#include "../../../Application/Util/Data_Structure/STList.h"
#include "../../../Math/STCore.h"
#include "../../../Math/Vector.h"
#include "../../../Math/Vertex.h"
#include "../../../Math/Matrix.h"
#include "STAnimationCommon.h"
#include "../../../Application/Util/File/STSerializeable.h"

struct STMeshNode{
    std::string m_Name;
    Matrix4f transform;
    STList<std::shared_ptr<STMeshNode>> m_Children;

    void save(std::ofstream& out){
        stUint numChildren = m_Children.size();
        STSerializableUtility::WriteString(m_Name.c_str(), out);
        transform.save(out);
        out.write((char*)&numChildren, sizeof(stUint));
        for(auto child : m_Children){
            child->save(out);
        }
    }

    void load(std::ifstream& in){
        stUint numChildren = 0;
        m_Name = STSerializableUtility::ReadString(in);
        transform.load(in);
        in.read((char*)&numChildren, sizeof(stUint));
        for(stUint i = 0; i < numChildren; i++){
            auto child = std::make_shared<STMeshNode>();
            child->load(in);
            m_Children.addLast(child);
        }
    }

    ~STMeshNode(){
        m_Children.clear();
    }
};

#define NUM_BONE_FOR_VERTS 4

/**
 * @brief Bone Weight Information
 */
struct STBoneWeight{
    stUint m_vertexID[NUM_BONE_FOR_VERTS];
    stReal m_weight[NUM_BONE_FOR_VERTS];

    inline void save(std::ofstream& out){
        out.write((char*)&m_vertexID, sizeof(m_vertexID));
        out.write((char*)&m_weight, sizeof(m_weight));
    }

    inline void load(std::ifstream& in){
        in.read((char*)&m_vertexID, sizeof(m_vertexID));
        in.read((char*)&m_weight, sizeof(m_weight));
    }

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

    void save(std::ofstream& out){
        STSerializableUtility::WriteString(m_name.c_str(), out);
        m_offsetMatrix.save(out);
        m_finalTransformation.save(out);
    }

    void load(std::ifstream& in){
        m_name = STSerializableUtility::ReadString(in);
        m_offsetMatrix.load(in);
        m_finalTransformation.load(in);
    }
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
    std::map<std::string, stUint> m_boneMap;
    std::vector<STBoneWeight> m_boneWeights;
    STList< std::shared_ptr<STAnimation> > m_Animations;
    std::shared_ptr<STMeshNode> m_Node;
    STList<std::shared_ptr<STBoneData>> m_BoneData;
    bool m_hasAnimations = false;
    bool m_hasBones = false;
    Matrix4f globalInverseMat;

    Vertex* getVertices(){ return &m_vertices[0]; }
    int* getIndicies(){ return &m_indices[0]; }

    inline stInt getVertexSize()const { return (stInt)m_vertices.size(); }
    inline stInt getIndexSize() const { return (stInt)m_indices.size(); }

    void save(std::ofstream& out){
        out.write((char*)&m_hasBones, sizeof(bool));
        out.write((char*)&m_hasAnimations, sizeof(bool));

        STSerializableUtility::WriteString(name.c_str(), out);
        STSerializableUtility::WriteString(materialKey.c_str(), out);

        stUint vertexSize = (stUint)m_vertices.size();
        out.write((char*)&vertexSize, sizeof(vertexSize));

        stUint indSize = (stUint)m_indices.size();
        out.write((char*)&indSize, sizeof(stUint));

        stUint boneCount = m_BoneData.size();
        out.write((char*)&boneCount, sizeof(boneCount));

        stUint boneWeightCount = (stUint)m_boneWeights.size();
        out.write((char*)&boneWeightCount, sizeof(stUint));

        stUint boneMapCount = (stUint)m_boneMap.size();
        out.write((char*)&boneMapCount, sizeof(stUint));

        stUint animCount = m_Animations.size();
        out.write((char*)&animCount, sizeof(stUint));

        for(auto v : m_vertices){
            v.save(out);
        }

        for(auto ind : m_indices){
            out.write((char*)&ind, sizeof(ind));
        }

        for(auto bone : m_BoneData){
            bone->save(out);
        }

        for(auto boneWeight : m_boneWeights){
            boneWeight.save(out);
        }

        for(auto bone : m_boneMap){
            STSerializableUtility::WriteString(bone.first.c_str(), out);
            out.write((char*)&bone.second, sizeof(stUint));
        }

        for(auto anim : m_Animations){
            anim->save(out);
        }
        m_Node->save(out);
        auto nodePeek = m_Node.get();
    }

    void load(std::ifstream& in, bool hasBones){
        m_hasBones = hasBones;
        bool hasAnim = false;
        in.read((char*)&hasAnim, sizeof(bool));
        m_hasAnimations = hasAnim;

        name = STSerializableUtility::ReadString(in);
        materialKey = STSerializableUtility::ReadString(in);

        stUint vertexSize, indSize, boneCount, boneWeightCount, boneMapCount, animCount;
        in.read((char*)&vertexSize, sizeof(stUint));
        in.read((char*)&indSize, sizeof(stUint));
        in.read((char*)&boneCount, sizeof(stUint));
        in.read((char*)&boneWeightCount, sizeof(stUint));
        in.read((char*)&boneMapCount, sizeof(stUint));
        in.read((char*)&animCount, sizeof(stUint));

        for(stUint i = 0; i < vertexSize; i++){
            auto v = Vector3D();
            auto t = Vector2D();
            auto n = Vector3D();
            v.load(in);
            t.load(in);
            n.load(in);
            m_vertices.emplace_back(Vertex(v, t, n));
        }

        for(stUint i = 0; i < indSize; i++){
            int ind = 0;
            in.read((char*)&ind, sizeof(int));
            m_indices.emplace_back(ind);
        }

        for(stUint i = 0; i < boneCount; i++){
            auto bone = std::make_shared<STBoneData>();
            bone->load(in);
            m_BoneData.addLast(bone);
        }

        for(stUint i = 0; i < boneWeightCount; i++){
            STBoneWeight boneWeight;
            boneWeight.load(in);
            m_boneWeights.push_back(boneWeight);
        }

        for(stUint i = 0; i < boneMapCount; i++){
            auto boneName = STSerializableUtility::ReadString(in);
            stUint value = 0;
            in.read((char*)&value, sizeof(stUint));
            m_boneMap[boneName] = value;
        }

        for(stUint i = 0; i < animCount; i++){
            auto anim = std::make_shared<STAnimation>();
            anim->load(in);
            m_Animations.addLast(anim);
        }
        m_Node = std::make_shared<STMeshNode>();
        m_Node->load(in);
        auto nodePeek = m_Node.get();
    }

    void load(std::ifstream& in){

    }
};

#endif //SWINGTECH1_STMESHCOMMON_H
