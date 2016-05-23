#ifndef WAHOO_STGRAPHICSCOMPONENT_H
#define WAHOO_STGRAPHICSCOMPONENT_H

#include <vector>

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "STComponent.h"

#include "Math/Vector.h"

struct SpriteSheet{
    int width, height;
    uint32_t rowCount, colCount, rowIndex, colIndex;
};

class STComponent;

class STGraphicsComponent : public STComponent{
public:
    STGraphicsComponent(Shader* shdr);
    STGraphicsComponent(Shader* shdr, Texture* tex);
    STGraphicsComponent(STMaterial* mat);
    STGraphicsComponent(const std::string& shdr);
    STGraphicsComponent(const std::string& shdrPath, const std::string& texPath);
    ~STGraphicsComponent(){
        delete m_shdr;
        if(useTexture) delete m_tex;
    }

    void addShdrUniform(const std::string& name, int value);
    void addShdrUniform(const std::string& name, float value);
    void addShdrUniform(const std::string& name, Vector3<stReal> value);
    void addShdrUniform(const std::string& name, Vector4<stReal> value);

    void setShdrUniform(const std::string& name, int value);
    void setShdrUniform(const std::string& name, float value);
    void setShdrUniform(const std::string& name, Vector3<stReal> value);
    void setShdrUniform(const std::string& name, Vector4<stReal> value);

    void addSpriteSheet(Texture* tex, uint32_t rowCount, uint32_t colCount);
    void setSpriteSheetIndex(int, int);
    void nextFrame();

    void setShader(Shader* shdr){
        m_shdr = shdr;
    }

    Shader* shdr(){
        if(useMaterial){
            return material->shdr();
        }else{
            return m_shdr;
        }

    }

    virtual void update(STGame * window, int delta){
        //Do Nothing

    }

    virtual void update(STEntity* entity, STGame* game, int delta);

    void draw(){
        //TODO Include shader handling and other stuff.
        if(!useMaterial){
            m_shdr->bind();
            m_shdr->updateUniforms(m_uniforms);
            if(useTexture) m_tex->bind(0);
        }else{
            material->update(m_uniforms);
        }
    }
private:
    SpriteSheet spriteSheet;
    Shader* m_shdr;
    Texture* m_tex;
    STMaterial* material;
    bool useTexture;
    bool useMaterial;
    std::vector<STShader::ShaderAttrib> m_uniforms;
};


#endif //WAHOO_STGRAPHICSCOMPONENT_H
