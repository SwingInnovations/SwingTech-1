#ifndef SWINGTECH1_STMESHLOADER_H
#define SWINGTECH1_STMESHLOADER_H

#include <map>

#include "STMeshCommon.h"
#include "../../../Graphics/STMaterial.h"
#include "../../../../include/assimp/Importer.hpp"
#include "../../../../include/assimp/postprocess.h"
#include "../../../../include/assimp/scene.h"

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
            (*dataMeshes).push_back(stMesh);
            (*materials).insert(std::pair<std::string, STMaterial*>(stMesh.materialKey, PopulateMaterial(mesh->mMaterialIndex, scene)));

            return false;
        }
        //Assuming there are multiple meshes now
        for(stUint k = 0, S = scene->mNumMeshes; k < S; k++){
            const aiMesh* mesh = scene->mMeshes[0];
            STMesh_Structure stMesh;
            stMesh.name = mesh->mName.C_Str();
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

            for(stUint j = 0, S = mesh->mNumVertices; j < S; j++){
                const aiVector3D* pos = &(mesh->mVertices[j]);
                const aiVector3D* texCoord = (mesh->HasTextureCoords(0)) ? &(mesh->mTextureCoords[0][j]) : &Z;
                const aiVector3D* normal = &(mesh->mNormals[j]);
                stMesh.m_vertices.push_back(Vertex(Vector3<stReal>(pos->x, pos->y, pos->z),
                                                   Vector2<stReal>(texCoord->x, texCoord->y),
                                                   Vector3<stReal>(normal->x, normal->y, normal->z)));
            }
            stMesh.m_indices = indices;
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
};

#endif //SWINGTECH1_STMESHLOADER_H
