#ifndef WAHOO_STGRAPHICSCOMPONENT_H
#define WAHOO_STGRAPHICSCOMPONENT_H

#include <vector>

#include "../../Graphics/Shader.h"
#include "../../Graphics/Texture.h"
#include "STComponent.h"

#include "../../Math/Vector.h"

struct SpriteSheet{
    int width, height;
    uint32_t rowCount, colCount, rowIndex, colIndex, row_cellSize, col_cellSize;
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
    void addShdrUniform(const std::string& name, Matrix4f value);
    void addShdrUniform_Texture(const std::string& name, stUint value);
    void addShdrUniform_CubeMap(const std::string& name, stUint value);
    void setDiffuseTexture(const std::string& fileName);
    void setNormalTexture(const std::string& fileName);

    void setShdrUniform(const std::string& name, int value);
    void setShdrUniform(const std::string& name, float value);
    void setShdrUniform(const std::string& name, Vector3<stReal> value);
    void setShdrUniform(const std::string& name, Vector4<stReal> value);
    void setShdrUniform(const std::string& name, Matrix4f value);
    void setShdrUniform_Texture(const std::string& name, stUint value);
    void setShdrUniform_CubeMap(const std::string& name, stUint value);

    void addSpriteSheet(Texture* tex, uint32_t rowCount, uint32_t colCount);
    void setSpriteSheetIndex(int, int);
    void setSpriteSheetRow(int);
    void nextFrame();

    inline void setShader(Shader* shdr){ m_shdr = shdr; }

    inline STMaterial* getMaterial(){ return m_material; }

    inline Shader* shdr(){
        if(useMaterial){
            return m_material->shdr();
        }else{
            return m_shdr;
        }

    }

    void update();
    inline void draw(){
        //TODO Include shader handling and other stuff.
        if(!useMaterial){
            m_shdr->bind();
            m_shdr->updateUniforms(m_uniforms);
            if(useTexture) m_tex->bind(0);
        }else{
            m_material->update(m_uniforms);
        }
    }

    std::vector<STShader::ShaderAttrib> &getUniforms();

    void draw(Transform& T, Camera& C);
private:
    SpriteSheet m_spriteSheet;
    Shader* m_shdr;
    Texture* m_tex;
    STMaterial* m_material;
    bool useTexture;
    bool useMaterial;
    std::vector<STShader::ShaderAttrib> m_uniforms;
};


#endif //WAHOO_STGRAPHICSCOMPONENT_H
