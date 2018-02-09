#ifndef SWINGTECH1_STASSETMANAGER_H
#define SWINGTECH1_STASSETMANAGER_H

#include <string>
#include <map>
#include "../Math/STCore.h"

class STEntity;


/**
 * @brief Baseclass for describing any asset.
 */
class STAsset{
public:
    enum STAsset_Type{ TEXTURE, MATERIAL, MESH, ENTITY };
    std::string getUID() const;
    std::string getName() const;
    virtual void init() = 0;
    virtual void deinit() = 0;

protected:
    stInt           m_accessLevel;        //Indicates Level in which asset is loaded. -1 indicates asset is global.
    std::string     m_uid;
    std::string     m_name;
    STAsset_Type    m_type;
    std::string     m_path;
    std::string     m_rawPath;
};

class STEntityAsset : public STAsset{

};

class STMaterialAsset : public STAsset{

};

class STTextureAsset : public STAsset{
public:
    void init() override;
    void deinit() override;
};

/**
 * @brief Manager for assets
 */
class STAssetManager {
public:
    static STAssetManager* _Instance;
    STAssetManager* Get();
    void Reference(const std::string& path);
    STAsset* Add(STEntity*);
    STAsset* Get(std::string uid);
    STAsset* Find(std::string name);
private:
    std::string                     m_manifestPath;
    std::map<std::string, STAsset*> m_assets;
};


#endif //SWINGTECH1_STASSETMANAGER_H
