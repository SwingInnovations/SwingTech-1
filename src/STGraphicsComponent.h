#ifndef WAHOO_STGRAPHICSCOMPONENT_H
#define WAHOO_STGRAPHICSCOMPONENT_H

#include <vector>

#include "Graphics/Shader.h"
#include "STComponent.h"

#include "Math/Vector.h"

class STGraphicsComponent : public STComponent{
public:
    ~STGraphicsComponent(){  }

    void addShdrAttrib(const std::string& name, int value);
    void addShdrAttrib(const std::string& name, float value);
    template<typename T> void addShdrAttrib(const std::string& name, Vector3<T> value);
    template<typename T> void addShdrAttrib(const std::string& name, Vector4<T> value);

    void setShdrAttrib(const std::string& name, int value);
    void setShdrAttrib(const std::string& name, float value);
    template<typename T> void setShdrAttrib(const std::string& name, Vector3<T> value);
    template<typename T> void setShdrAttrib(const std::string& name, Vector4<T> value);

    void draw(){
        //TODO Include shader handling and other stuff.
    }
private:
    std::vector<STShader::ShaderAttrib> m_uniforms;
};


#endif //WAHOO_STGRAPHICSCOMPONENT_H
