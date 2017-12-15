#include "GLSkinnedMesh.h"

GLSkinnedMesh::GLSkinnedMesh() {

}

GLSkinnedMesh::GLSkinnedMesh(STMesh_Structure &structure) {
    std::vector<Vector3D> vertex;
    std::vector<Vector2D> texCoord;
    std::vector<Vector3D> normal;
    std::vector<Vector3D> tangent;
    std::vector<Vector3D> biTangent;
    std::vector<stUint> boneIDs;
    std::vector<stReal> boneWeights;

    stUint numVert = (stUint)structure.getVertexSize();
    m_drawCount = (stUint)structure.getIndexSize();
    for(auto v : structure.m_vertices){
        vertex.push_back(*v.getVertex());
        texCoord.push_back(*v.getTexCoord());
        normal.push_back(*v.getNormal());
    }
    tangent = genTangent(vertex, texCoord);
    biTangent = genBiTangent(vertex, texCoord);

    auto Bones = structure.m_boneWeights;
    for(auto bone : Bones){
        for(auto v : bone.m_vertexID){
            boneIDs.push_back(v);
        }
        for(auto w : bone.m_weight){
            boneWeights.push_back(w);
        }
    }

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    glGenBuffers(NUM_BUFFERS, m_VBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(vertex[0]), &vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(normal[0]), &normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[TANGENT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(tangent[0]), &tangent[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[BITANGENT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert*sizeof(biTangent[0]), &biTangent[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[BONE_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boneIDs[0]) * boneIDs.size(), &boneIDs[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_UNSIGNED_INT, 4*(sizeof(stUint)), (const GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO[BONE_WEIGHT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boneWeights[0]) * boneWeights.size(), &boneWeights[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBO[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_drawCount * sizeof(structure.m_indices[0]), &structure.m_indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLSkinnedMesh::~GLSkinnedMesh() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(NUM_BUFFERS, m_VBO);
}

void GLSkinnedMesh::draw() {
    if(m_VAO && m_drawCount > 0 && m_drawCount % 3 == 0){
        glBindVertexArray(m_VAO);

        glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }else{
        std::cout << "Something is wrong" << std::endl;
    }
}

void GLSkinnedMesh::draw(int drawMode) {
    if(m_VAO && m_drawCount > 0 && m_drawCount % 3 == 0){
        GLenum mode;
        if(drawMode == STMesh::DrawMode::LINES){
            mode = GL_LINES;
        }else if(drawMode == STMesh::DrawMode::TRIANGLES){
            mode = GL_TRIANGLES;
        }else if(drawMode == STMesh::DrawMode::LINE_LOOP){
            mode = GL_LINE_LOOP;
        }

        glBindVertexArray(m_VAO);

        glDrawElements(mode, m_drawCount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }else{
        std::cerr << "Something is wrong in Draw Calls. " << std::endl;
    }
}
