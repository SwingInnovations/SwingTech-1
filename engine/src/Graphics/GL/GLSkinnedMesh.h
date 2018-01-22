#ifndef SWINGTECH1_GLSKINNEDMESH_H
#define SWINGTECH1_GLSKINNEDMESH_H

#include <GL/glew.h>
#include "../../Entity/Util/STMesh.h"

class GLSkinnedMesh  : public STMesh{
public:
    GLSkinnedMesh();
    explicit GLSkinnedMesh(STMesh_Structure &structure);
    ~GLSkinnedMesh();
    void draw() override;
    void draw(int drawMode) override;
    void load(std::ifstream& in, bool hasBones) override ;
private:
    enum{
        VERTEX_BUFFER,
        TEXCOORD_BUFFER,
        NORMAL_BUFFER,
        INDEX_BUFFER,
        TANGENT_BUFFER,
        BITANGENT_BUFFER,
        BONE_BUFFER,
        BONE_WEIGHT_BUFFER,
        NUM_BUFFERS
    };
    GLuint m_VAO;
    GLuint m_VBO[NUM_BUFFERS];
    std::string m_meshName;
    stUint m_drawCount;
    stUint m_numIndicies;
};


#endif //SWINGTECH1_GLSKINNEDMESH_H
