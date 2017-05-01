#ifndef WAHOO_STMATERIAL_H
#define WAHOO_STMATERIAL_H

#include <vector>

#include "Texture.h"
#include "Shader.h"
#include "GL/GLTexture.h"

class GLTexture;
class STGraphics;

struct ShaderList{
    std::string vertShader;
    std::string fragShader;
    std::string geomShader;
};

struct TextureList{
    std::string diffuseTex;
    std::string normalTex;
    std::string specularTex;
    std::string alphaTex;
};

class STMaterial{
public:
    STMaterial();

    STMaterial(ShaderList, TextureList);

    /*!
     * @name STMaterial
     * @param shdr STShader for use
     * @return
     */
    STMaterial(Shader* shdr);

    STMaterial(Shader* shdr, Texture* tex){
        shader = shdr;
        texture = tex;
        initBaseUniforms();

    }

    ~STMaterial(){
        delete texture;
        delete shader;

    }

    /*!
     * @param fileName Adds diffuse texture and assigns to texture index 0
     */
    void setDiffuseTexture(const std::string& fileName);

    void setNormalTexture(const std::string& fileName);

    void setBaseColor(Vector3<stReal> color){
        m_baseColor = color;
    }

    std::vector<STShader::ShaderAttrib>& getUniforms(){ return _uniforms; }

    void initBaseUniforms()
     {
         setBaseColor( Vector3<stReal>(1,1,1) );
         _uniforms.push_back(STShader::ShaderAttrib("Material.BaseColor", STShader::VEC3, STShader::toString(m_baseColor)));
     }


    /*!
     * @details Main update that gets called in the render loop.
     */
    inline void update(){
        shader->bind();
        shader->updateUniforms(_uniforms);
        for(unsigned int i = 0; i < texture->getTextureCount(); i++){
            texture->bind(i);
        }
    }

    Shader* shdr(){ return shader; }
    Texture* tex(){ return texture; }

    inline void update(std::vector<STShader::ShaderAttrib> entityUniforms){
        shader->bind();
        shader->updateUniforms(_uniforms);
        shader->updateUniforms(entityUniforms);
        if(texture->getTextureCount() > 31){
            texture->bind(0);
        }else{
            for(unsigned int i = 0, S = texture->getTextureCount(); i < S; i++){
                texture->bind(i);
            }
        }
    }


    void draw(std::vector<STShader::ShaderAttrib>& entityUniforms, Transform& T, Camera& C);
    void draw(std::vector<STShader::ShaderAttrib> &entityUniforms, std::vector<STShader::ShaderAttrib> originalMaterialUniforms,
              Transform &T, Camera &C);
private:
    void init_GLShaders(ShaderList list);
    void init_GLTextures(TextureList list);
    Texture* texture;
    Shader* shader;
    Vector3<stReal> m_baseColor;
    bool useTexture;
    std::vector<STShader::ShaderAttrib> _uniforms;
};

#endif //WAHOO_STMATERIAL_H
