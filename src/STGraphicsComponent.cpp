#include "STGraphicsComponent.h"

STGraphicsComponent::STGraphicsComponent(Shader *shdr) {
    m_shdr = shdr;
    useTexture = false;
}

STGraphicsComponent::STGraphicsComponent(Shader *shdr, Texture *tex) {
    m_shdr = shdr;
    m_tex = tex;
    useTexture = true;
}

void STGraphicsComponent::addShdrAttrib(const std::string &name, int value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::INT, STShader::toString(value)));
}

void STGraphicsComponent::addShdrAttrib(const std::string &name, float value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::FLOAT, STShader::toString(value)));
}

void STGraphicsComponent::addShdrAttrib(const std::string &name, Vector3<stReal> value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::VEC3, STShader::toString(value)));
}

void STGraphicsComponent::addShdrAttrib(const std::string &name, Vector4<stReal> value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::VEC4, STShader::toString(value)));
}

void STGraphicsComponent::setShdrAttrib(const std::string &name, int value) {
    for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
        }
    }
}

void STGraphicsComponent::setShdrAttrib(const std::string &name, float value) {
    for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
        }
    }
}

void STGraphicsComponent::setShdrAttrib(const std::string &name, Vector3<stReal> value) {
    for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
        }
    }
}

void STGraphicsComponent::setShdrAttrib(const std::string &name, Vector4<stReal> value) {
    for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
        }
    }
}