#ifndef WAHOO_SCOMPONENT_H
#define WAHOO_SCOMPONENT_H

#include <vector>
#include <string>

#include "Math/Transform.h"
#include "Graphics/Camera.h"
#include "Graphics/Shader.h"

class Transform;
class Shader;

class SComponent {
    SComponent(){
        m_transform = new Transform();
        m_Shader = 0;
    }

    void addShdrAttrib(const std::string& name, int value);
    void addShdrAttrib(const std::string& name, float value);
    template<typename T> void addShdrAttrib(const std::string& name, Vector3<T> value);
    template<typename T> void addShdrAttrib(const std::string& name, Vector4<T> value);

    void setShdrAttrib(const std::string& name, int value);
    void setShdrAttrib(const std::string& name, float value);
    template<typename T> void setShdrAttrib(const std::string& name, Vector3<T> value);
    template<typename T> void setShdrAttrib(const std::string& name, Vector4<T> value);

    Transform* transform(){ return m_transform; }

    virtual void draw(Camera*){}
private:
    Transform* m_transform;
    Shader* m_Shader;
    std::vector<STShader::ShaderAttrib> m_uniforms;
};
#endif //WAHOO_SCOMPONENT_H
