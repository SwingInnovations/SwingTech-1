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

void STGraphicsComponent::addShdrUniform(const std::string &name, Matrix4f value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::MAT4, STShader::toString(value)));
}

void STGraphicsComponent::addShdrUniform_Texture(const std::string &name, stUint value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(value)));
}

void STGraphicsComponent::addShdrUniform_CubeMap(const std::string &name, stUint value) {
    m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::CUBE_MAP, STShader::toString(value)));
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

void STGraphicsComponent::setShdrUniform_Texture(const std::string &name, stUint id, stUint index) {
    bool uniformFound = false;
    for(stUint i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(Vector2<stInt>(id, index));
            uniformFound = true;
        }
    }
    if(!uniformFound){
        m_uniforms.push_back(STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(Vector2<stInt>(id, index))));
    }
}


void STGraphicsComponent::setShdrUniform(const std::string &name, Matrix4f value) {
    bool uniformFound;
    for(stUint i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
            uniformFound = true;
        }
    }
    if(!uniformFound) addShdrUniform(name, value);
}

void STGraphicsComponent::setShdrUniform_Texture(const std::string &name, stUint value) {
    bool uniformFound;
    for(stUint i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
            uniformFound = true;
        }
    }
    if(!uniformFound) addShdrUniform_Texture(name, value);
}

void STGraphicsComponent::setShdrUniform_CubeMap(const std::string &name, stUint value) {
    bool uniformFound;
    for(stUint i = 0, S = m_uniforms.size(); i < S; i++){
        if(m_uniforms[i].name == name){
            m_uniforms[i].value = STShader::toString(value);
            uniformFound = true;
            return;
        }
    }
    if(!uniformFound) addShdrUniform_CubeMap(name, value);
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
    m_material->draw(m_uniforms, T, C);
}

std::vector<STShader::ShaderAttrib> &STGraphicsComponent::getUniforms() {
    return m_uniforms;
}

void STGraphicsComponent::setDiffuseTexture(const std::string &fileName) {
    m_material->setDiffuseTexture(fileName);
}

void STGraphicsComponent::setNormalTexture(const std::string &fileName) {
    m_material->setNormalTexture(fileName);
}
