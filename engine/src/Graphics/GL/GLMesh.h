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

    explicit GLMesh(STRect* rect);

    explicit GLMesh(STQuad* quad);

    void load(std::ifstream& in, bool hasBones) override;

    explicit GLMesh(STCube* cube);
    GLMesh(float vert[], int vSize, float tex[], int tSize, int ind[], int indSize);
    ~GLMesh();

    void draw() override;
    void draw(int drawMode) override;
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
