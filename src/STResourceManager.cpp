#include "STResourceManager.h"

STResourceManager::STResourceManager() {

}

STResourceManager::~STResourceManager() {

}

void STResourceManager::addShader(std::string key, Shader *shdr) {
    _shaders[key] = shdr;
}

void STResourceManager::addTexture(std::string key, Texture *texture) {
    _textures[key] = texture;
}

Shader* STResourceManager::getShader(std::string key) {
    return _shaders[key];
}

Texture* STResourceManager::getTexture(std::string key) {
    return _textures[key];
}