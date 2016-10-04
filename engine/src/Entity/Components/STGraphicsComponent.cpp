#include "STGraphicsComponent.h"
#include "../../Graphics/GL/GLShader.h"

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
    m_material = mat;
    useMaterial = true;
}

void STGraphicsComponent::addShdrUniform(const std::string &name, int value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::INT, STShader::toString(value)));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, float value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::FLOAT, STShader::toString(value)));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector3<stReal> value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::VEC3, STShader::toString(value)));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector4<stReal> value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::VEC4, STShader::toString(value)));
}

void STGraphicsComponent::setShdrUniform(const std::string &name, int value) {
    for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
        }
    }
}

void STGraphicsComponent::setShdrUniform(const std::string &name, float value) {
    bool uniformFound;
    for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
            uniformFound=true;
        }
    }
    if(!uniformFound)
        addShdrUniform(name,value);
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector3<stReal> value) {
    bool uniformFound;
    for(unsigned int i = 0, S = (unsigned int)m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
            uniformFound=true;
        }
    }
    if(!uniformFound)
        addShdrUniform(name,value);
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector4<stReal> value) {
    bool uniformFound;
    for(unsigned int i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
            uniformFound=true;
        }
    }
    if(!uniformFound)
        addShdrUniform(name,value);
}

void STGraphicsComponent::addSpriteSheet(Texture *tex, uint32_t rowCount, uint32_t colCount) {
    if(!useTexture) {
        useTexture = true;
        m_tex = tex;
    }
    m_spriteSheet.width = tex->getTextureWidth();
    m_spriteSheet.height = tex->getTextureHeight();
    m_spriteSheet.row_cellSize = rowCount / tex->getTextureHeight();
    m_spriteSheet.col_cellSize = colCount / tex->getTextureWidth();
    addShdrUniform("sprite-xOffset", 0.0f);
    addShdrUniform("sprite-yOffset", 0.0f);
}

void STGraphicsComponent::setSpriteSheetIndex(int row, int col) {
    if( row < m_spriteSheet.rowCount )m_spriteSheet.rowIndex = (uint32_t)row; else m_spriteSheet.rowIndex = 0;
    if( col < m_spriteSheet.colCount )m_spriteSheet.colIndex = (uint32_t)col; else m_spriteSheet.colIndex = 0;
}

void STGraphicsComponent::nextFrame() {
    if(m_spriteSheet.colIndex < m_spriteSheet.colCount){
        m_spriteSheet.colIndex++;
    }else{
        m_spriteSheet.colIndex = 0;
    }
    stReal colOffset = m_spriteSheet.colIndex * m_spriteSheet.col_cellSize;
    setShdrUniform("sprite-xOffset", colOffset);
}

void STGraphicsComponent::setSpriteSheetRow(int row) {
    if(row < m_spriteSheet.rowCount) m_spriteSheet.rowIndex = (uint32_t)row; else m_spriteSheet.rowIndex = 0;
    stReal rowOffset = m_spriteSheet.rowIndex * m_spriteSheet.row_cellSize;
    setShdrUniform("sprite-yOffset", rowOffset);
}

void STGraphicsComponent::update() {

}

void STGraphicsComponent::draw(Transform &T, Camera &C) {
    m_material->draw(m_uniforms, T, C);
}

std::vector<STShader::ShaderAttrib> &STGraphicsComponent::getUniforms() {
    return m_uniforms;
}
