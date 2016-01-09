#ifndef WAHOO_STGRAPHICSCOMPONENT_H
#define WAHOO_STGRAPHICSCOMPONENT_H

#include <vector>

#include "Graphics/Shader.h"
#include "STComponent.h"

#include "Math/Vector.h"

class STGraphicsComponent : public STComponent{
public:
    STGraphicsComponent(Shader* shdr);
    ~STGraphicsComponent(){  }

    void addShdrAttrib(const std::string& name, int value);
    void addShdrAttrib(const std::string& name, float value);
    template<typename T> void addShdrAttrib(const std::string& name, Vector3<T> value);
    template<typename T> void addShdrAttrib(const std::string& name, Vector4<T> value);

    void setShdrAttrib(const std::string& name, int value);
    void setShdrAttrib(const std::string& name, float value);
    template<typename T> void setShdrAttrib(const std::string& name, Vector3<T> value);
    template<typename T> void setShdrAttrib(const std::string& name, Vector4<T> value);

    void setShader(Shader* shdr){
        m_shdr = shdr;
    }

    Shader* shdr(){ return m_shdr; }

    virtual void update(STechWindow* window, int delta){
        //Do Nothing

    }

    void draw(){
        //TODO Include shader handling and other stuff.
        for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++) {
            if (m_uniforms[i].type == STShader::INT) {
                m_shdr->update(m_uniforms[i].name, STShader::toInt(m_uniforms[i].value));
            } else if (m_uniforms[i].type == STShader::FLOAT) {
                m_shdr->update(m_uniforms[i].name, STShader::toFloat(m_uniforms[i].value));
            } else if (m_uniforms[i].type == STShader::VEC3) {
                m_shdr->update(m_uniforms[i].name, STShader::toVector3(m_uniforms[i].value));
            } else {
                m_shdr->update(m_uniforms[i].name, STShader::toVector4(m_uniforms[i].value));
            }
        }
        m_shdr->bind();
    }
private:
    Shader* m_shdr;
    std::vector<STShader::ShaderAttrib> m_uniforms;
};


#endif //WAHOO_STGRAPHICSCOMPONENT_H
