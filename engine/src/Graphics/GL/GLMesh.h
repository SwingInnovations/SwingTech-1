#ifndef WAHOO_GLMESH_H
#define WAHOO_GLMESH_H

#include <string>
#include <vector>

#if __MINGW32__
#include "../../../include/GL/glew.h"
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../Entity/Util/STMesh.h"

class GLMesh : public STMesh{
public:
    GLMesh();
    //GLMesh(const std::string& fileName);
    GLMesh(STMesh_Structure structure);
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
    GLuint  m_VAO;
    GLuint m_VBO[NUM_BUFFERS];
    std::string m_fileName;
    uint32_t m_drawCount;
    stUint m_numIndicies;
};


#endif //WAHOO_GLMESH_H
