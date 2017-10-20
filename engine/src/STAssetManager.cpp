#include "STAssetManager.h"

STAssetManager* STAssetManager::_Instance = nullptr;

STAssetManager *STAssetManager::Get() {
    if(_Instance == nullptr){
        _Instance = new STAssetManager();
    }
    return _Instance;
}

/**
 *
 * @param entity Entity you wish to add to Entity Folders
 * @return
 */
STAsset *STAssetManager::Add(STEntity *entity) {
    return nullptr;
}
/*!
 * Returns Based on uid
 * @param uid
 * @return
 */
STAsset *STAssetManager::Get(std::string uid) {
    return nullptr;
}

/**
 * @brief Returns the Asset if found by name. (If duplicate.. first is returned.)
 * @param name
 * @return
 */
STAsset *STAssetManager::Find(std::string name) {
    for(auto m : m_assets){
        if(m.second->getName() == name){
            return m.second;
        }
    }
    return nullptr;
}

/**
 * @brief Reference a folder for raw files. Generates a new folder with converted, "EngineFriendly" Format.
 * @param path
 */
void STAssetManager::Reference(const std::string &path) {

}

std::string STAsset::getUID() const {
    return m_uid;
}

std::string STAsset::getName() const {
    return m_name;
}

void STTextureAsset::init() {

}

void STTextureAsset::deinit() {

}


