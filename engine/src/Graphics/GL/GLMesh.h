#ifndef WAHOO_GLMESH_H
#define WAHOO_GLMESH_H

#include <string>
#include <vector>

#include "../../../include/GL/glew.h"

#include "../../STMesh.h"

class GLMesh : public STMesh{
public:
    GLMesh();
    GLMesh(const std::string& fileName, int type);
    GLMesh(STRect* rect);
    GLMesh(STQuad* quad);
    GLMesh(STCube* cube);
    GLMesh(float vert[], int vSize, float tex[], int tSize, int ind[], int indSize);
    ~GLMesh();

    void draw();
    void draw(int drawMode);
private:
    enum{
        VERTEX_BUFFER,
        TEXCOORD_BUFFER,
        NORMAL_BUFFER,
        INDEX_BUFFER,
        TANGENT_BUFFER,
        BITANGENT_BUFFER,
        NUM_BUFFERS
    };
    GLuint  _VAO;
    GLuint _VBO[NUM_BUFFERS];
    std::string _fileName;
    uint32_t _drawCount;
};


#endif //WAHOO_GLMESH_H
