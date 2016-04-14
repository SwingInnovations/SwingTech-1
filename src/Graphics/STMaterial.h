#ifndef WAHOO_STMATERIAL_H
#define WAHOO_STMATERIAL_H

#include "Texture.h"
#include "Shader.h"

class STMaterial{
    STMaterial();
    STMaterial(Shader* shdr);

    void addDiffuse(Texture* tex);
    void addDiffuse(Vector3<stReal> diffuse);
    void addSpecular(Texture* tex);
    void addSpecular(Vector3<stReal> specular);
    void addNormal(Vector3<stReal> normal);
    void addNormal(Texture* normal);
private:
    Texture* texture;
    Shader* shader;
    bool useTexture;
};

#endif //WAHOO_STMATERIAL_H
