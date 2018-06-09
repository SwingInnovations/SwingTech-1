#ifndef WAHOO_SHADER_H
#define WAHOO_SHADER_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

#include "../Math/Vector.h"
#include "../Entity/Transform.h"
#include "../Application/Util/File/STSerializeable.h"

class Transform;
class Camera;
class STCamera;
class Matrix4f;

/*!
 * @brief Contains information to describing how uniforms are updated.
 */
namespace STShader{
	enum ShadingModel : unsigned char {
		PBR = 0
	};

   enum Type : unsigned char{
    INT = 0,
       FLOAT = 1,
       VEC3 = 2,
       VEC4 = 3,
       MAT4 = 4,
       TEX = 5,
       CUBE_MAP = 6,
       STRING = 7,
       VEC2 = 8,
       TEX1DARR = 9,
       TEX2DARR = 10
   };

    /*!
     *
     * @param val - Input integer
     * @return Stringified integer for uniform use.
     */
    static std::string toString(const int& val) {
        std::ostringstream buff;
        buff << val;
        return buff.str();
    }

    /*!
     *
     * @param val Input float
     * @return Stringified float for uniform use.
     */
    static std::string toString(const float& val) {
        std::ostringstream buff;
        buff << val;
        return buff.str();
    }

    static std::string toString(const Vector2<stInt>& vec){
        std::ostringstream buff;
        buff << vec.getX() << "/" << vec.getY();
        return buff.str();
    }

    template<typename T> static std::string toString(const Vector2<T>& val) {
        std::ostringstream buff;
        buff << val.getX() << "/" << val.getY();
        return buff.str();
    }

    /*!
     *
     * @param val Input Vector3
     * @return Stringified Vector3 for uniform use.
     */
    template<typename T> static std::string toString(const Vector3<T>& val) {
        std::ostringstream buff;
        buff << val.getX() << "/" << val.getY() << "/" << val.getZ();
        return buff.str();
    }

    /*!
     *
     * @param val Input Vector4
     * @return Strngified Vector4 for uniform use.
     */
    template<typename T> static std::string toString(const Vector4<T>& val){
        std::ostringstream buff;
        buff << val.getX() << "/" << val.getY() << "/" << val.getZ() << "/" << val.getW();
        return buff.str();
    }

    /*!
     * @param mat Input Matrix
     * @return Stringified Matrix for uniform use.
     */
    static std::string toString(const Matrix4f& mat){
        std::ostringstream buff;
        for(stUint i = 0, I = 4; i < I; i++){
            for(stUint j = 0, J = 4; j < J; j++){
                buff << mat.m[i][j] << " ";
            }
        }
        return buff.str();
    }

    static std::string toString(const stUint& val){
        std::ostringstream buff;
        buff << val;
        return buff.str();
    }

    /*!
     *
     * @param val Input stringified integer uniform
     * @return Integer value
     */
    static int toInt(const std::string val){
        return atoi(val.c_str());
    }

    /*!
     *
     * @param val Input stringified float uniform
     * @return Float value
     */
    static float toFloat(const std::string val){
        return (float)atof(val.c_str());
    }

    static stUint toSTUint(const std::string val){
        return (stUint)atol(val.c_str());
    }

    static Vector2<stReal> toVector2(const std::string& val){
        stReal _x = 0, _y = 0;
        _x = (stReal)atof(val.substr(0, val.find('/')).c_str());
        _y = (stReal)atof(val.substr(val.find('/')+1).c_str());
        return Vector2<stReal>(_x, _y);
    }

    /*!
     *
     * @param val Input stringified Vector3 uniform
     * @return Vector3 value as Vector3<stReal>
     */
    static Vector3<stReal> toVector3(const std::string& val){
        stReal _x = 0;
        stReal _y = 0;
        stReal _z = 0;
        _x = (stReal)atof(val.substr(0, val.find('/')).c_str());
        _y = (stReal)atof(val.substr(val.find('/')+1, val.find_last_of('/') ).c_str());
        _z = (stReal)atof(val.substr(val.find_last_of('/')+1).c_str());
        Vector3<stReal> ret(_x, _y, _z);
        return ret;
    }

    /*!
     *
     * @param value Input stringified Vector4 uniform
     * @return value as Vector4<stReal>
     */
    static Vector4<stReal> toVector4(const std::string& value){
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

    /** Converts Serialized Matrix to Matrix4f
     *
     * @param value Matrix4f serialized
     * @return Matrix4f non-serialized
     */
    static Matrix4f toMatrix4f(const std::string& value){
        std::vector<stReal> elements;
        Matrix4f ret;
        std::stringstream str(value);
        stReal temp;
        stUint counter = 0;
        while(str >> temp) elements.push_back(temp);
        for(stUint i = 0, I = 4; i < I; i++){
            for(stUint j = 0, J = 4; j < J; j++){
                ret.m[i][j] = elements.at(counter);
                counter++;
            }
        }
        return ret;
    }

    struct ShaderAttrib{

        ShaderAttrib(){

        }
        /*!
         *
         * @param name Unique name for the uniform
         * @param type Type of uniform. Options: {INT, FLOAT, VEC3, VEC4}
         * @param value Stringified uniform value
         * @return
         */
        ShaderAttrib(const std::string& name, const int type, const std::string& value){
            this->name = name;
            this->type = type;
            this->value = value;
        }

        void save(std::ofstream& out){
            out.write((char*)&type, sizeof(int));
            STSerializableUtility::WriteString(name.c_str(), out);
            STSerializableUtility::WriteString(value.c_str(), out);
        }

        void load(std::ifstream& in){
            in.read((char*)&type, sizeof(int));
            name = STSerializableUtility::ReadString(in);
            value = STSerializableUtility::ReadString(in);
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
	/**
	 * @brief Binds shader to current OpenGL Context
	 */
    virtual void bind(){  }
    virtual void unbind(){ }
    virtual void update(Transform& trans){  }
    virtual void update(Camera& cam){  }
    virtual void update(STCamera* cam){}
    virtual void update(Transform& trans, Camera& cam){ }
    virtual void update(Transform& trans, STCamera* camera){ }
    virtual void update(const std::string& name, int val){}
    virtual void update(const std::string& name, float val){ }
    virtual void update(const std::string& name, Vector2<stReal> val){ }
    virtual void update(const std::string& name, Vector3<stReal> val){ }
    virtual void update(const std::string& name, Vector4<stReal> val){  }
    virtual void update(const std::string& name, Matrix4f mat){ }
    virtual void update_Texture(const std::string& name, stUint){ }
    virtual void update_Texture(const std::string& name, Vector2<stInt> val){ }
    virtual void update_Texture2DArray(const std::string& name, Vector2<stInt> val){}
    virtual void update_CubeMap(const std::string& name, stUint){ }
    void updateUniforms(std::map<std::string, STShader::ShaderAttrib>);
    virtual std::string getShaderName(){ return NULL; }
    virtual void save(std::ofstream& out) = 0;
    virtual void load(std::ifstream& in) = 0;
    virtual ~Shader(){}
protected:
    std::map<std::string, std::string> m_refPath;
};

#endif //WAHOO_SHADER_H
