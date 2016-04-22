#ifndef WAHOO_STRESOURCEMANAGER_H
#define WAHOO_STRESOURCEMANAGER_H

#include <vector>
#include <map>
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/STMaterial.h"

class STResourceManager {
public:
    STResourceManager();
    ~STResourceManager();

    void addShader(std::string, Shader*);
    void addTexture(std::string, Texture*);
    void addMaterial(std::string, STMaterial*);

    Shader* getShader(std::string);
    Texture* getTexture(std::string);
    STMaterial* getMaterial(std::string);
private:
    std::map<std::string, Shader*> _shaders;
    std::map<std::string, Texture*> _textures;
    std::map<std::string, STMaterial*> _materials;
};


#endif //WAHOO_STRESOURCEMANAGER_H
