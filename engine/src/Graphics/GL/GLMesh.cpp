#include "GLMesh.h"
#include "../../Entity/Components/STMeshComponent.h"

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

GLMesh::GLMesh(STRect *rect) {
    _drawCount = 6;
    int numVert = 4;
    std::vector<int> indicies;

    std::vector<Vector3<stReal>> initialCoordinates;
    stReal x = rect->points.at(0);
    stReal y = rect->points.at(1);
    stReal width = rect->points.at(2);
    stReal height = rect->points.at(3);

    initialCoordinates.push_back(Vector3<stReal>(x, y, 0.0));
    initialCoordinates.push_back(Vector3<stReal>(x, y + height, 0.0));
    initialCoordinates.push_back(Vector3<stReal>(x + width, y + height, 0.0));
    initialCoordinates.push_back(Vector3<stReal>(x + width, y, 0.0));

    std::vector<Vector2<stReal>> texCoords;
    texCoords.push_back(Vector2<stReal>(0.0f, 1.0f));
    texCoords.push_back(Vector2<stReal>(0.0f, 0.0f));
    texCoords.push_back(Vector2<stReal>(1.0f, 0.0f));
    texCoords.push_back(Vector2<stReal>(1.0f, 1.0f));

    indicies.push_back(0);
    indicies.push_back(1);
    indicies.push_back(2);
    indicies.push_back(2);
    indicies.push_back(3);
    indicies.push_back(0);

    Vector3<stReal> norm(0.0f, 0.0f, 0.0f);

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(NUM_BUFFERS, _VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(initialCoordinates[0]), &initialCoordinates[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(norm), &norm, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBO[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _drawCount * sizeof(indicies[0]), &indicies[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLMesh::GLMesh(STCube* cube){
    _drawCount = (uint32_t)cube->getIndexSize();
    int numVert = cube->getVertexSize();

    std::vector<Vector3<stReal>> vertex;
    std::vector<Vector2<stReal>> texCoord;
    std::vector<Vector3<stReal>> normal;

    for(uint32_t i = 0; i < numVert; i++){
        vertex.push_back(*cube->getVerticies()[i].getVertex());
        texCoord.push_back(*cube->getVerticies()[i].getTexCoord());
        normal.push_back(*cube->getVerticies()[i].getNormal());
    }

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(NUM_BUFFERS, _VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(vertex[0]), &vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(normal[0]), &normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBO[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _drawCount * sizeof(cube->getIndicies()[0]), &cube->getIndicies()[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}


GLMesh::GLMesh(STQuad *quad) {
    _drawCount = (uint32_t)quad->getIndSize();
    int numVert = quad->getVertSize();

    std::vector<Vector3<stReal>> vertex;
    std::vector<Vector2<stReal>> texCoord;
    std::vector<Vector3<stReal>> normal;

    for(uint32_t i = 0; i < numVert; i++){
        vertex.push_back(*quad->verticies[i].getVertex());
        texCoord.push_back(*quad->verticies[i].getTexCoord());
        normal.push_back(*quad->verticies[i].getNormal());
    }

    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(NUM_BUFFERS, _VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(vertex[0]), &vertex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(texCoord[0]), &texCoord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[NORMAL_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVert * sizeof(normal[0]), &normal[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBO[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _drawCount * sizeof(quad->indicies[0]), &quad->indicies[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLMesh::GLMesh(float *vert, int vSize, float *tex, int tSize, int *ind, int indSize) {
    _drawCount = indSize;
    glGenVertexArrays(1, &_VAO);
    glBindVertexArray(_VAO);

    glGenBuffers(NUM_BUFFERS, _VBO);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, vSize * sizeof(vert[0]), &vert[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO[TEXCOORD_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, tSize * sizeof(tex[0]), &tex[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _VBO[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indSize* sizeof(ind[0]), &ind[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLMesh::~GLMesh() {
    glDeleteVertexArrays(1, &_VAO);
}

void GLMesh::draw() {
    glBindVertexArray(_VAO);

    glDrawElements(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void GLMesh::draw(int drawMode) {
    GLenum mode;
        if(drawMode == STMesh::DrawMode::LINES){
            mode = GL_LINES;
        }else if(drawMode == STMesh::DrawMode::TRIANGLES){
            mode = GL_TRIANGLES;
        }else if(drawMode == STMesh::DrawMode::LINE_LOOP){
            mode = GL_LINE_LOOP;
        }

        glBindVertexArray(_VAO);

        glDrawElements(mode, _drawCount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
}
