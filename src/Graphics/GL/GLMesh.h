#ifndef WAHOO_GLMESH_H
#define WAHOO_GLMESH_H

#include <string>
#include <vector>

#include "../../../ext/GL/glew.h"

#include "../../STMesh.h"

class GLMesh : public STMesh{
public:
    GLMesh();
    GLMesh(const std::string& fileName, int type);
    GLMesh(SWRect* rect);
    GLMesh(STQuad* quad);

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
