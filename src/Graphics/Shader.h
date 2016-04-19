#ifndef WAHOO_SHADER_H
#define WAHOO_SHADER_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

#include "../Math/Vector.h"
#include "../Math/Transform.h"

class Transform;
class Camera;
class Matrix4f;

namespace STShader{
   enum Type{
    INT = 0,
       FLOAT = 1,
       VEC3 = 2,
       VEC4 = 3,
       MAT4 = 4,
       STRING = 5
   };

    static std::string toString(int val){
        std::ostringstream buff;
        buff << val;
        return buff.str();
    }

    static std::string toString(float val){
        std::ostringstream buff;
        buff << val;
        return buff.str();
    }

    template<typename T> static std::string toString(Vector3<T> val){
        std::ostringstream buff;
        buff << val.getX() << "/" << val.getY() << "/" << val.getZ();
        return buff.str();
    }

    template<typename T> static std::string toString(Vector4<T> val){
        std::ostringstream buff;
        buff << val.getX() << "/" << val.getY() << "/" << val.getZ() << "/" << val.getW();
        return buff.str();
    }

    static int toInt(std::string val){
        return atoi(val.c_str());
    }

    static float toFloat(std::string val){
        return (float)atof(val.c_str());
    }

    static Vector3<stReal> toVector3(std::string& val){
        stReal _x = 0;
        stReal _y = 0;
        stReal _z = 0;
        _x = (stReal)atof(val.substr(0, val.find('/')).c_str());
        _y = (stReal)atof(val.substr(val.find('/')+1, val.find_last_of('/') ).c_str());
        _z = (stReal)atof(val.substr(val.find_last_of('/')+1).c_str());
        Vector3<stReal> ret(_x, _y, _z);
        return ret;
    }

    static Vector4<stReal> toVector4(std::string& value){
        stReal _x = 0, _y = 0, _z = 0, _w = 0;
        std::string vX = value.substr(0, value.find('/'));
        std::string d1 = value.substr(value.find('/')+1);
        std::string vY = d1.substr(0, d1.find('/'));
        std::string d2 = d1.substr(d1.find('/')+1);
        std::string vZ = d2.substr(0, d2.find('/'));
        std::string vW = d2.substr(d2.find_last_of('/')+1);
        _x = (stReal)atof(vX.c_str());
        _y = (stReal)atof(vY.c_str());
        _z = (stReal)atof(vZ.c_str());
        _w = (stReal)atof(vW.c_str());
        Vector4<stReal> ret(_x, _y, _z, _w);
        return ret;
    }

    struct ShaderAttrib{
        ShaderAttrib(const std::string& name, const int type, const std::string& value){
            this->name = name;
            this->type = type;
            this->value = value;
        }
        std::string name;
        int type;
        std::string value;
    };
};
class Shader {
    //set for use with GL or Vulkan
public:
    Shader(){;}
    Shader(const std::string& filePath){;}
    Shader(const std::string& vFilePath, const std::string& fFilePath){;}
    virtual void bind(){  }
    virtual void unbind(){ }
    virtual void update(Transform& trans){  }
    virtual void update(Camera& cam){  }
    virtual void update(Transform& trans, Camera& cam){ }
    virtual void update(const std::string& name, int val){}
    virtual void update(const std::string& name, float val){ }
    virtual void update(const std::string& name, Vector3<stReal> val){ }
    virtual void update(const std::string& name, Vector4<stReal> val){  }
    void updateUniforms(std::vector<STShader::ShaderAttrib> _uniforms);
    virtual std::string getShaderName(){ return NULL; }
    virtual ~Shader(){}
    static void SetGraphicsMode(bool val){
        USE_GL = val;
    }
private:
    static bool USE_GL;
};

#endif //WAHOO_SHADER_H
