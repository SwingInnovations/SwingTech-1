#ifndef WAHOO_STMESHCOMPONENT_H
#define WAHOO_STMESHCOMPONENT_H

#include "STComponent.h"
#include "Math/Vector.h"
#include "Math/Vertex.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "../ext/GL/glew.h"

namespace STMesh{
  enum{
    OBJ = 0,
      GEX = 1,
      FBX = 2
  };
};

class OBJMesh{
public:
    OBJMesh();
    OBJMesh(const std::string& filename);
    virtual ~OBJMesh();

    Vertex* getVerticies(){ return &verticies[0]; }
    int* getIndicies(){ return &indicies[0]; }

    int getVerticiesSize(){ return (int)verticies.size(); }
    int getIndiciesSize(){ return (int)indicies.size(); }

    std::vector<int> indicies;
    std::vector<Vertex> verticies;
private:

    std::vector<Vector3<stReal>> _vertex;
    std::vector<Vector2<stReal>> _texCoord;
    std::vector<Vector3<stReal>> _normal;
    std::vector<int> _index;
};

class STMeshComponent : public STComponent{

public:
    STMeshComponent(const std::string& fileName, int type);

    void draw(){
        glBindVertexArray(m_VAO);

        glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
    }

private:
    std::vector<Vector3<stReal>>genTangent(std::vector<Vector3<stReal>>& vert, std::vector<Vector2<stReal>>& tex){
        std::vector<Vector3<stReal>> ret;

        for(unsigned int i = 0, S = vert.size(); i < S; i+= 3){
            Vector3<stReal> v0 = vert[i];
            Vector3<stReal> v1 = vert[i+1];
            Vector3<stReal> v2 = vert[i+2];

            Vector2<stReal> uv0 = tex[i+0];
            Vector2<stReal> uv1 = tex[i+1];
            Vector2<stReal> uv2 = tex[i+2];

            Vector3<stReal> dP1 = v1 - v0;
            Vector3<stReal> dP2 = v2 - v0;

            Vector2<stReal> dUV1 = uv1 - uv0;
            Vector2<stReal> dUV2 = uv2 - uv0;

            float r = 1.0f / (dUV1.getX() * dUV2.getY() - dUV1.getY() * dUV2.getX());
            Vector3<stReal> a = (dP1 * dUV2.getY()) * r;
            Vector3<stReal> b = (dP2 * dUV1.getY()) * r;
            Vector3<stReal> tangent = a - b;

            ret.push_back(tangent);
            ret.push_back(tangent);
            ret.push_back(tangent);
        }

        return ret;
    }

    std::vector<Vector3<stReal>>genBiTangent(std::vector<Vector3<stReal>>& vert, std::vector<Vector2<stReal>>& tex){
        std::vector<Vector3<stReal>> ret;

        for(unsigned int i = 0, S = vert.size(); i < S; i+= 3){
            Vector3<stReal> v0 = vert[i];
            Vector3<stReal> v1 = vert[i+1];
            Vector3<stReal> v2 = vert[i+2];

            Vector2<stReal> uv0 = tex[i+0];
            Vector2<stReal> uv1 = tex[i+1];
            Vector2<stReal> uv2 = tex[i+2];

            Vector3<stReal> dP1 = v1 - v0;
            Vector3<stReal> dP2 = v2 - v0;

            Vector2<stReal> dUV1 = uv1 - uv0;
            Vector2<stReal> dUV2 = uv2 - uv0;

            float r = 1.0f / (dUV1.getX() * dUV2.getY() - dUV1.getY() * dUV2.getX());
            Vector3<stReal> a = (dP1 * dUV2.getY()) * r;
            Vector3<stReal> b = (dP2 * dUV1.getY()) * r;
            Vector3<stReal> tangent = b - a;

            ret.push_back(tangent);
            ret.push_back(tangent);
            ret.push_back(tangent);
        }

        return ret;
    }

    enum{
        VERTEX_BUFFER,
        TEXCOORD_BUFFER,
        NORMAL_BUFFER,
        INDEX_BUFFER,
        TANGENT_BUFFER,
        BITANGENT_BUFFER,
        NUM_BUFFERS
    };

    GLuint m_VAO;
    GLuint m_VBO[NUM_BUFFERS];
    std::string m_fileName;

    unsigned int m_drawCount;
};


#endif //WAHOO_STMESHCOMPONENT_H
