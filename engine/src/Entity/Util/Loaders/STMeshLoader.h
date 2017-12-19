#ifndef SWINGTECH1_STMESHLOADER_H
#define SWINGTECH1_STMESHLOADER_H

#include <map>

#include "../../../Graphics/GL/GLShader.h"

#include "STMeshCommon.h"
#include "../../../Graphics/STMaterial.h"
#include "../../../../include/assimp/Importer.hpp"
#include "../../../../include/assimp/postprocess.h"
#include "../../../../include/assimp/scene.h"
#include "STAnimationCommon.h"

/**
 * @brief Refer to this file when making a custom loader.
 */

class MeshLoader{
public:
    /**
     * Loads a mesh from path.
     * @param fileName
     * @return
     */
    static STMesh_Structure Load(const std::string& fileName){
        Assimp::Importer importer;
        std::vector<int> indicies;
        STMesh_Structure stMesh;
        const aiScene* scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if(!scene){
            std::cerr << "Failed to load file: " << fileName << std::endl;
            return stMesh;
        }
        const aiMesh* mesh = scene->mMeshes[0];
        for(stUint i = 0, S = mesh->mNumFaces; i < S; i++){
            const aiFace& faces = mesh->mFaces[i];
            assert(faces.mNumIndices == 3);
            indicies.push_back(faces.mIndices[0]);
            indicies.push_back(faces.mIndices[1]);
            indicies.push_back(faces.mIndices[2]);
        }
        stMesh.name = mesh->mName.C_Str();
        stMesh.materialKey = "";

        if(mesh->mNumAnimMeshes != 0){

        }
        if(mesh->mNumBones != 0){
            stMesh.m_hasBones = true;
        }

        const aiVector3D Z(0.f, 0.f, 0.f);
        for(stUint j = 0, S = mesh->mNumVertices; j < S; j++){
            const aiVector3D* pPos = &(mesh->mVertices[j]);
            const aiVector3D* pTexCoord = (mesh->HasTextureCoords(0)) ? &(mesh->mTextureCoords[0][j]) : &Z;
            const aiVector3D* pNormal = &(mesh->mNormals[0]);
            stMesh.m_vertices.push_back(Vertex(Vector3<stReal>(pPos->x, pPos->y, pPos->z),
                                               Vector2<stReal>(pTexCoord->x, pTexCoord->y),
                                               Vector3<stReal>(pNormal->x, pNormal->y, pNormal->z)));
        }
        stMesh.m_indices = indicies;
        return stMesh;
    }
    /**
     * Loads a mesh from the specified path, and all its submeshes. Submeshes will be children of the "Root" object.
     * @param fileName Path to File
     * @param errFlag  If an error occured somewhere in import, stored here
     * @param tags     Names of Submesh
     * @param dataMesh - MeshData itself.
     * @return
     */
    static bool Validate(const std::string& fileName, bool* errFlag, std::vector<STMesh_Structure>* dataMeshes, std::map<std::string, STMaterial*>* materials){
        Assimp::Importer importer;
        std::vector<int> indices;

        const aiScene* scene = importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);
        if(!scene){
            std::cerr << "Failed to load: " << fileName << std::endl;
            *errFlag = false;
            return false;
        }

        if(scene->mNumMeshes == 1){
            const aiMesh* mesh = scene->mMeshes[0];
            for(stUint i = 0, S = mesh->mNumFaces; i < S; i++){
                const aiFace& faces = mesh->mFaces[i];
                assert(faces.mNumIndices == 3);
                indices.push_back(faces.mIndices[0]);
                indices.push_back(faces.mIndices[1]);
                indices.push_back(faces.mIndices[2]);
            }

            STMesh_Structure stMesh;
            stMesh.m_node = new STMeshNode;
            stMesh.globalInverseMat = Matrix4f::From(scene->mRootNode->mTransformation.Inverse());
            if(scene->mNumAnimations > 0){
                stMesh.m_hasAnimations = true;
                for(stUint i = 0, S = scene->mNumAnimations; i < S; i++){
                    auto * anim = new STAnimation;
                    anim->name = scene->mAnimations[i]->mName.C_Str();
                    anim->m_Duration = (stReal)scene->mAnimations[i]->mDuration;
                    anim->m_TicksPerSecond = (stReal)scene->mAnimations[i]->mTicksPerSecond;
                    for(stUint j = 0; j < scene->mAnimations[i]->mNumChannels; j++){
                        auto * nodeAnim = new STNodeAnim;
                        nodeAnim->name = scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str();
                        for(stUint k = 0; k < scene->mAnimations[i]->mChannels[j]->mNumPositionKeys; k++){
                            nodeAnim->m_positions.addLast(new STVectorKey( (stReal)scene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mTime,Vector3<stReal>::From(scene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mValue)));
                        }
                        for(stUint k = 0; k < scene->mAnimations[i]->mChannels[j]->mNumRotationKeys; k++){
                            nodeAnim->m_rotations.addLast(new STQuaternionKey( (stReal)scene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mTime, Quaternion::From(scene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mValue)));
                        }
                        for(stUint k = 0; k < scene->mAnimations[i]->mChannels[j]->mNumScalingKeys; k++){
                            nodeAnim->m_scalings.addLast(new STVectorKey( (stReal)scene->mAnimations[i]->mChannels[j]->mScalingKeys[k].mTime,Vector3<stReal>::From(scene->mAnimations[i]->mChannels[j]->mScalingKeys[k].mValue)));
                        }
                        anim->m_channels.addLast(nodeAnim);
                    }
                    stMesh.m_animations.addLast(anim);
                }
            }

            if(scene->mRootNode->mNumChildren > 0){
                std::function<void(aiNode*, STMeshNode*)> recursiveAddNode;
                recursiveAddNode = [&recursiveAddNode](aiNode* rootNode, STMeshNode* node) -> void {
                    if(rootNode->mNumChildren < 1) return;
                    auto newNode = new STMeshNode;
                    newNode->m_Name = rootNode->mName.C_Str();
                    newNode->transform = Matrix4f::From(rootNode->mTransformation);
                    node->m_children.addLast(newNode);
                    for(stUint i = 0, S = rootNode->mNumChildren; i < S; i++){
                        recursiveAddNode(rootNode->mChildren[i], newNode);
                    }
                };
                stMesh.m_node = new STMeshNode;
                stMesh.m_node->m_Name = scene->mRootNode->mName.C_Str();
                stMesh.m_node->transform = Matrix4f::From(scene->mRootNode->mTransformation);
                for(stUint i = 0; i < scene->mRootNode->mNumChildren; i++){
                    recursiveAddNode(scene->mRootNode->mChildren[i], stMesh.m_node);
                }
            }

            stMesh.name = mesh->mName.C_Str();
            aiString matName;
            scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_NAME, matName);
            stMesh.materialKey = matName.C_Str();
            const aiVector3D Z(0.f, 0.f, 0.f);
            for(stUint j = 0, S = mesh->mNumVertices; j < S; j++){
                const aiVector3D* pPos = &(mesh->mVertices[j]);
                const aiVector3D* pNormal = &(mesh->mNormals[j]);
                const aiVector3D* pTexCoord = (mesh->HasTextureCoords(0)) ? &(mesh->mTextureCoords[0][j]) : &Z;
                stMesh.m_vertices.push_back(Vertex(Vector3<stReal>(pPos->x, pPos->y, pPos->z),
                                                   Vector2<stReal>(pTexCoord->x, pTexCoord->y),
                                                   Vector3<stReal>(pNormal->x, pNormal->y, pNormal->z)));
            }
            stMesh.m_indices = indices;
            stMesh.m_boneWeights.resize(mesh->mNumVertices);
            stMesh.m_baseVertex = 0;
            stMesh.m_baseIndex = 0;
            stUint numBones = 0;

            if(mesh->mNumBones > 0){
                stMesh.m_hasBones = true;
                for(stUint i = 0, L = mesh->mNumBones; i < L; i++){
                    stUint boneIndex = 0;
                    auto boneData = new STBoneData;
                    std::string boneName = boneData->m_name = mesh->mBones[i]->mName.C_Str();

                    if(stMesh.m_boneMap.find(boneName) == stMesh.m_boneMap.end()){
                        boneIndex = numBones;
                        numBones++;
                        stMesh.m_boneData.addLast(boneData);
                        stMesh.m_boneData[boneIndex]->m_offsetMatrix = Matrix4f::From(mesh->mBones[i]->mOffsetMatrix);
                        stMesh.m_boneMap[boneName] = boneIndex;
                    }else{
                        boneIndex = stMesh.m_boneMap[boneName];
                    }

                    for(stUint j = 0, K = mesh->mBones[i]->mNumWeights; j < K; j++){
                        stUint vID = stMesh.m_baseVertex + mesh->mBones[i]->mWeights[j].mVertexId;
                        stReal weight = mesh->mBones[i]->mWeights[j].mWeight;
                        stMesh.m_boneWeights[vID].addBoneData(boneIndex, weight);
                    }
                }
            }
            (*dataMeshes).push_back(stMesh);
            (*materials).insert(std::pair<std::string, STMaterial*>(stMesh.materialKey, PopulateMaterial(mesh->mMaterialIndex, scene, stMesh.m_hasBones)));
            return false;
        }

        //Assuming there are multiple meshes now
        stUint baseIndex = 0;
        stUint baseVertex = 0;
        for(stUint k = 0, S = scene->mNumMeshes; k < S; k++){
            const aiMesh* mesh = scene->mMeshes[k];
            STMesh_Structure stMesh;
            stMesh.m_node = new STMeshNode;
            stMesh.m_baseVertex = baseVertex;
            stMesh.m_baseIndex = baseIndex;
            baseVertex += mesh->mNumVertices;
            baseIndex += mesh->mNumFaces*3;
            stMesh.name = mesh->mName.C_Str();
            stMesh.globalInverseMat = Matrix4f::From(scene->mRootNode->mTransformation.Inverse());
            if(scene->mNumAnimations > 0){
                stMesh.m_hasAnimations = true;
                for(stUint i = 0, T = scene->mNumAnimations; i < T; i++){
                    auto * anim = new STAnimation;
                    anim->name = scene->mAnimations[i]->mName.C_Str();
                    anim->m_Duration = (stReal)scene->mAnimations[i]->mDuration;
                    anim->m_TicksPerSecond = (stReal)scene->mAnimations[i]->mTicksPerSecond;
                    for(stUint j = 0; j < scene->mAnimations[i]->mNumChannels; j++){
                        auto * nodeAnim = new STNodeAnim;
                        nodeAnim->name = scene->mAnimations[i]->mChannels[j]->mNodeName.C_Str();
                        for(stUint l = 0; l < scene->mAnimations[i]->mChannels[j]->mNumPositionKeys; l++){
                            nodeAnim->m_positions.addLast(new STVectorKey( (stReal)scene->mAnimations[i]->mChannels[j]->mPositionKeys[l].mTime,Vector3<stReal>::From(scene->mAnimations[i]->mChannels[j]->mPositionKeys[l].mValue)));
                        }
                        for(stUint l = 0; l < scene->mAnimations[i]->mChannels[j]->mNumRotationKeys; l++){
                            nodeAnim->m_rotations.addLast(new STQuaternionKey( (stReal)scene->mAnimations[i]->mChannels[j]->mRotationKeys[l].mTime, Quaternion::From(scene->mAnimations[i]->mChannels[j]->mRotationKeys[l].mValue)));
                        }
                        for(stUint l = 0; l < scene->mAnimations[i]->mChannels[j]->mNumScalingKeys; l++){
                            nodeAnim->m_scalings.addLast(new STVectorKey( (stReal)scene->mAnimations[i]->mChannels[j]->mScalingKeys[l].mTime,Vector3<stReal>::From(scene->mAnimations[i]->mChannels[j]->mScalingKeys[l].mValue)));
                        }
                        anim->m_channels.addLast(nodeAnim);
                    }
                    stMesh.m_animations.addLast(anim);
                }
            }

            if(scene->mRootNode->mNumChildren > 0){
                std::function<void(aiNode*, STMeshNode*)> recursiveAddNode;
                recursiveAddNode = [&recursiveAddNode](aiNode* rootNode, STMeshNode* node) -> void {
                    if(rootNode->mNumChildren < 1) return;
                    auto newNode = new STMeshNode;
                    newNode->m_Name = rootNode->mName.C_Str();
                    newNode->transform = Matrix4f::From(rootNode->mTransformation);
                    node->m_children.addLast(newNode);
                    for(stUint i = 0, T = rootNode->mNumChildren; i < T; i++){
                        recursiveAddNode(rootNode->mChildren[i], newNode);
                    }
                };
                stMesh.m_node = new STMeshNode;
                stMesh.m_node->m_Name = scene->mRootNode->mName.C_Str();
                stMesh.m_node->transform = Matrix4f::From(scene->mRootNode->mTransformation);
                for(stUint i = 0; i < scene->mRootNode->mNumChildren; i++){
                    recursiveAddNode(scene->mRootNode->mChildren[i], stMesh.m_node);
                }
            }

            aiString matName;
            scene->mMaterials[mesh->mMaterialIndex]->Get(AI_MATKEY_NAME, matName);
            const aiVector3D Z(0.f, 0.f, 0.f);

            for(stUint i = 0; i < mesh->mNumFaces; i++){
                const aiFace& faces = mesh->mFaces[i];
                assert(faces.mNumIndices == 3);
                indices.push_back(faces.mIndices[0]);
                indices.push_back(faces.mIndices[1]);
                indices.push_back(faces.mIndices[2]);

            }

            for(stUint j = 0, K = mesh->mNumVertices; j < S; j++){
                const aiVector3D* pos = &(mesh->mVertices[j]);
                const aiVector3D* texCoord = (mesh->HasTextureCoords(0)) ? &(mesh->mTextureCoords[0][j]) : &Z;
                const aiVector3D* normal = &(mesh->mNormals[j]);
                stMesh.m_vertices.push_back(Vertex(Vector3D(pos->x, pos->y, pos->z),
                                                   Vector2D(texCoord->x, texCoord->y),
                                                   Vector3D(normal->x, normal->y, normal->z)));
            }

            stMesh.m_indices = indices;
            stUint numBones = 0;
            if(mesh->mNumBones > 0){
                stMesh.m_hasBones = true;
                for(stUint i = 0, L = mesh->mNumBones; i < L; i++){
                    stUint boneIndex = 0;
                    auto boneData = new STBoneData;
                    std::string boneName = boneData->m_name = mesh->mBones[i]->mName.C_Str();

                    if(stMesh.m_boneMap.find(boneName) == stMesh.m_boneMap.end()){
                        boneIndex = numBones;
                        numBones++;
                        stMesh.m_boneData.addLast(boneData);
                        stMesh.m_boneData[boneIndex]->m_offsetMatrix = Matrix4f::From(mesh->mBones[i]->mOffsetMatrix);
                        stMesh.m_boneMap[boneName] = boneIndex;
                    }else{
                        boneIndex = stMesh.m_boneMap[boneName];
                    }

                    for(stUint j = 0, K = mesh->mBones[i]->mNumWeights; j < K; j++){
                        stUint vID = stMesh.m_baseVertex + mesh->mBones[i]->mWeights[j].mVertexId;
                        stReal weight = mesh->mBones[i]->mWeights[j].mWeight;
                        stMesh.m_boneWeights[vID].addBoneData(boneIndex, weight);
                    }
                }
            }

            (*dataMeshes).push_back(stMesh);
        }
        return true;
    }

    static STMaterial* PopulateMaterial(stUint index, const aiScene* scene){
        const aiMaterial* material = scene->mMaterials[index];
        STMaterial* ret = new STMaterial(new GLShader("standard"));
        aiColor3D diffuse;
        aiColor3D specular;
        aiColor3D ambient;
        if(material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS){
            ret->setDiffuseColor(STColor(diffuse.r, diffuse.g, diffuse.b, 1.0));
        }

        //Handle Textures later on
        if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS){
                ret->setDiffuseTexture(path.C_Str());
            }
        }
        if(material->GetTextureCount(aiTextureType_NORMALS) > 0){
            aiString path;
            if(material->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS){
                ret->setNormalTexture(path.C_Str());
            }
        }
        return ret;
    }

    static STMaterial* PopulateMaterial(stUint index, const aiScene* scene, bool flag){
        const aiMaterial* material = scene->mMaterials[index];
        STMaterial* ret;
        if(flag)
            ret = new STMaterial(new GLShader("standardSkinned", "standard"));
        else
            ret = new STMaterial(new GLShader("standard"));
        aiColor3D diffuse;
        aiColor3D specular;
        aiColor3D ambient;
        if(material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse) == AI_SUCCESS){
            ret->setDiffuseColor(STColor(diffuse.r, diffuse.g, diffuse.b, 1.0));
        }

        //Handle Textures later on
        if(material->GetTextureCount(aiTextureType_DIFFUSE) > 0){
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS){
                ret->setDiffuseTexture(path.C_Str());
            }
        }
        if(material->GetTextureCount(aiTextureType_NORMALS) > 0){
            aiString path;
            if(material->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS){
                ret->setNormalTexture(path.C_Str());
            }
        }
        return ret;
    }
};

#endif //SWINGTECH1_STMESHLOADER_H
