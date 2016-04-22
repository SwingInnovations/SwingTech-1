#include "STGraphicsComponent.h"
#include "Graphics/GL/GLShader.h"

STGraphicsComponent::STGraphicsComponent(Shader *shdr) {
    m_shdr = shdr;
    useTexture = false;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(Shader *shdr, Texture *tex) {
    m_shdr = shdr;
    m_tex = tex;
    useTexture = true;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(const std::string &shdr) {
    m_shdr = new GLShader(shdr);
    useTexture = false;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(const std::string &shdrPath, const std::string &texPath) {
    m_shdr = new GLShader(shdrPath);
    m_tex = new GLTexture(texPath);
    useTexture = true;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(STMaterial *mat) {
    material = mat;
    useMaterial = true;
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
    for(unsigned int i = 0, S = (unsigned int)m_uniforms.size(); i < S; i++){
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

void STGraphicsComponent::addSpriteSheet(Texture *tex, uint32_t rowCount, uint32_t colCount) {
    if(!useTexture) useTexture = true;
    m_tex = tex;
    spriteSheet.width = tex->getTextureWidth();
    spriteSheet.height = tex->getTextureHeight();
}

void STGraphicsComponent::setSpriteSheetIndex(int row, int col) {
    spriteSheet.rowIndex = (uint32_t)row;
    spriteSheet.colIndex = (uint32_t)col;
}

void STGraphicsComponent::nextFrame() {

}