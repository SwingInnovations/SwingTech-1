#ifndef WAHOO_STMESH_H
#define WAHOO_STMESH_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "../../Math/Shape/Shape.h"
#include "../../Math/Shape/Rect.h"
#include "../../Math/Shape/Quad.h"
#include "../../Math/Shape/Cube.h"
#include "Loaders/STMeshCommon.h"


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
    static bool Validate(const std::string& fileName, int* typeFlag, std::vector<std::string>* tags, std::vector<STMesh_Structure>* meshes);
    static bool Validate(const std::string& fileName, bool* errFlag, std::vector<std::string>* tags, std::vector<STMesh_Structure>* meshes);
    static bool Validate(const std::string& fileName, bool* errFlag, std::vector<STMesh_Structure>* meshes, std::map<std::string, STMaterial*>* materials);
    STMesh(){}
    STMesh(const std::string& fileName, int type){}
    STMesh(Shape& shape){ }
    STMesh(STRect* rect){ }
    STMesh(STQuad* quad){  }
    STMesh(STCube* cube){  }
    STMesh(float vert[], int vSize, float tex[], int tSize, int ind[], int indSize){ }
    ~STMesh(){  }

    virtual void draw(){}
    virtual void draw(int drawMode){  }

    std::vector<Vector3<stReal>> new_GenTangent(std::vector<Vector3<stReal>>& normal){
        std::vector<Vector3<stReal>> ret;
        Vector3<stReal> Z(0.0f, 0.0f, 1.0f);
        Vector3<stReal> Y(0.0f, 1.0f, 0.0f);
        for(stUint i = 0; i < normal.size(); i++){
            Vector3<stReal> c1 = normal.at(i);
            c1 = c1.cross(Z).normalize();
            Vector3<stReal> c2 = normal.at(i);
            c2 = c2.cross(Y).normalize();
            if(c1.getLength() > c2.getLength() ){
                ret.push_back(c1);
            }else{
                ret.push_back(c2);
            }
        }
        return ret;
    }

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
