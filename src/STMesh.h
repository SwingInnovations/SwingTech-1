#ifndef WAHOO_STMESH_H
#define WAHOO_STMESH_H

#include <string>
#include "Math/Shape/Shape.h"
#include "Math/Shape/Rect.h"
#include "Math/Shape/Quad.h"

class STMesh {
public:
    enum Type{
        OBJ = 0,
        GEX = 1,
        FBX = 2
    };

    enum DrawMode{
        LINES = 0,
        TRIANGLES = 1,
        LINE_LOOP = 2,
    };

    STMesh(){}
    STMesh(const std::string& fileName, int type){}
    STMesh(Shape& shape){ }
    STMesh(SWRect* rect){ }
    STMesh(STQuad* quad){  }

    virtual void draw(){}
    virtual void draw(int drawMode){  }

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
};


#endif //WAHOO_STMESH_H
