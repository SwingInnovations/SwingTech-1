#include "GLMesh.h"
#include "../../STMeshComponent.h"

GLMesh::GLMesh() {

}

GLMesh::GLMesh(const std::string &fileName, int type) {
    std::vector<Vector3<stReal>> vertex;
    std::vector<Vector2<stReal>> texCoord;
    std::vector<Vector3<stReal>> normal;
    std::vector<Vector3<stReal>> tangent;
    std::vector<Vector3<stReal>> biTangent;
    std::vector<int> index;

    _fileName = fileName;

    int numVert = 0;

    if(type == STMesh::OBJ){
        auto tMesh = new OBJMesh(fileName);
        numVert = tMesh->getVerticiesSize();
        _drawCount = tMesh->getIndiciesSize();
        vertex.reserve(numVert);
        texCoord.reserve(numVert);
        normal.reserve(numVert);

        for(unsigned int i = 0; i < numVert; i++){
            vertex.push_back(*tMesh->verticies[i].getVertex());
            texCoord.push_back(*tMesh->verticies[i].getTexCoord());
            normal.push_back(*tMesh->verticies[i].getNormal());
        }
        index = tMesh->indicies;
        tangent = genTangent(vertex, texCoord);
        biTangent = genBiTangent(vertex, texCoord);
        delete tMesh;
    }

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(NUM_BUFFERS, _VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert*sizeof(vertex[0]), &vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(normal[0]), &normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[TANGENT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert* sizeof(tangent[0]), &tangent[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[BITANGENT_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert*sizeof(&biTangent[0]), &biTangent[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBO[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _drawCount * sizeof(index[0]), &index[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLMesh::GLMesh(SWRect *rect) {

}

GLMesh::GLMesh(STQuad *quad) {

}

void GLMesh::draw() {

}

void GLMesh::draw(int drawMode) {
    STMesh::draw(drawMode);
}
