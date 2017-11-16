#include "STGraphicsComponent.h"
#include "../../Graphics/GL/GLShader.h"

STGraphicsComponent::STGraphicsComponent(const STGraphicsComponent &copy) {
    this->m_material = copy.m_material;
    this->m_entity = copy.m_entity;
}

STGraphicsComponent::STGraphicsComponent(Shader *shdr) {
    m_shdr = shdr;
    useTexture = false;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(const std::string &shdr) {
    m_shdr = new GLShader(shdr);
    useTexture = false;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(STMaterial *mat) {
    m_material = mat;
    useMaterial = true;
}

void STGraphicsComponent::addShdrUniform(const std::string &name, int value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::INT, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, float value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::FLOAT, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector2<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC2, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector3<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC3, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector4<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC4, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Matrix4f value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::MAT4, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform_Texture(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform_Texture2DArray(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX2DARR, STShader::toString(value))));
}

void STGraphicsComponent::addShdrUniform_CubeMap(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0) m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::CUBE_MAP, STShader::toString(value))));
}

void STGraphicsComponent::setShdrUniform(const std::string &name, int value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
}

void STGraphicsComponent::setShdrUniform(const std::string &name, float value) {
    if(m_Uniforms.count(name) > 0)m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector2<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector3<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector4<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
}

void STGraphicsComponent::setShdrUniform_Texture(const std::string &name, stUint id, stUint index) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(Vector2<stInt>(id, index));
    else m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(Vector2<stInt>(id, index)))));
}


void STGraphicsComponent::setShdrUniform(const std::string &name, Matrix4f value) {
    if(m_Uniforms.count(name) > 0)m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
}

void STGraphicsComponent::setShdrUniform_Texture(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform_Texture(name, value);
}

void STGraphicsComponent::setShdrUniform_Texture2DArray(const std::string &name, stUint id, stUint index) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(Vector2<stInt>(id, index));
    else m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(Vector2<stInt>(id, index)))));
}

void STGraphicsComponent::setShdrUniform_CubeMap(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform_CubeMap(name, value);
}

void STGraphicsComponent::addSpriteSheet(Texture *tex, uint32_t rowCount, uint32_t colCount) {
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
    std::cout << "Calling Next Frame" << std::endl;
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
    //m_material->draw(m_uniforms, T, C);
    m_material->draw(m_Uniforms, T, C);
}

void STGraphicsComponent::setDiffuseTexture(const std::string &fileName) {
    m_material->setDiffuseTexture(fileName);
}

void STGraphicsComponent::setNormalTexture(const std::string &fileName) {
    m_material->setNormalTexture(fileName);
}

std::map<std::string, STShader::ShaderAttrib> &STGraphicsComponent::GetUniforms() {
    return m_Uniforms;
}

void STGraphicsComponent::draw() {
    //m_material->draw(m_uniforms);
    //m_material->draw();
}


