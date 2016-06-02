#include "STResourceManager.h"

STResourceManager::STResourceManager() {

}

STResourceManager::~STResourceManager() {

}

void STResourceManager::addShader(std::string key, Shader *shdr) {
    m_shaders[key] = shdr;
}

void STResourceManager::addTexture(std::string key, Texture *texture) {
    m_textures[key] = texture;
}

void STResourceManager::addMaterial(std::string key, STMaterial *material) {
    m_materials[key] = material;
}

Shader* STResourceManager::getShader(std::string key) {
    return m_shaders[key];
}

Texture* STResourceManager::getTexture(std::string key) {
    return m_textures[key];
}

STMaterial *STResourceManager::getMaterial(std::string key) {
    return m_materials[key];
}
