#include "SComponent.h"

void SComponent::addShdrAttrib(const std::string &name, int value){
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::INT, STShader::toString(value)));
}

void SComponent::addShdrAttrib(const std::string& name, float value){
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::FLOAT, STShader::toString(value)));
}

template<typename T> void SComponent::addShdrAttrib(const std::string &name, Vector3<T> value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::VEC3, STShader::toString(value)));
}

template<typename T> void SComponent::addShdrAttrib(const std::string &name, Vector4<T> value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::VEC4, STShader::toString(value)));
}

void SComponent::setShdrAttrib(const std::string &name, int value) {
    for(int i = 0; i < m_uniforms.size(); i++){
        if(m_uniforms[i].name == name){ m_uniforms[i].value = STShader::toString(value); }
    }
}

void SComponent::setShdrAttrib(const std::string &name, float value) {
    for(int i = 0; i < m_uniforms.size(); i++){
        if(m_uniforms[i].name == name){ m_uniforms[i].value = STShader::toString(value); }
    }
}

template<typename T> void SComponent::setShdrAttrib(const std::string &name, Vector3<T> value) {
    for(int i = 0; i < m_uniforms.size(); i++){
        if(m_uniforms[i].name == name){ m_uniforms[i].value = STShader::toString(value); }
    }
}

template<typename T> void SComponent::setShdrAttrib(const std::string &name, Vector4<T> value) {
    for(int i = 0; i < m_uniforms.size(); i++){
        if(m_uniforms[i].name == name){ m_uniforms[i].value = STShader::toString(value); }
    }
}