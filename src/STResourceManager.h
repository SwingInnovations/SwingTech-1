#ifndef WAHOO_STRESOURCEMANAGER_H
#define WAHOO_STRESOURCEMANAGER_H

#include <vector>
#include <map>
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

class STResourceManager {
public:
    STResourceManager();
    ~STResourceManager();

    void addShader(std::string, Shader*);
    void addTexture(std::string, Texture*);

    Shader* getShader(std::string);
    Texture* getTexture(std::string);
private:
    std::map<std::string, Shader*> _shaders;
    std::map<std::string, Texture*> _textures;
};


#endif //WAHOO_STRESOURCEMANAGER_H
