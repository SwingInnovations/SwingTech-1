#ifndef WAHOO_STMATERIAL_H
#define WAHOO_STMATERIAL_H

#include <vector>

#include "Texture.h"
#include "Shader.h"

class GLTexture;
class STGraphics;


class STMaterial{
public:
    STMaterial();
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
    void setDiffuseTexture(const std::string& fileName){
        texture->addTexture(fileName, 0);
    }

    void setNormalTexure(const std::string& fileName){
        texture->addTexture(fileName, 1);
    }

    void setBaseColor(Vector3<stReal> color){
        m_baseColor = color;
    }

    void initBaseUniforms()
     {
         setBaseColor( Vector3<stReal>(.7,0,0 ) );
         _uniforms.push_back(STShader::ShaderAttrib("Material.BaseColor", STShader::VEC3, STShader::toString(m_baseColor)));
         _uniforms.push_back(STShader::ShaderAttrib("Material.Diffuse_Tex", STShader::VEC3, "0"));
         _uniforms.push_back(STShader::ShaderAttrib("Material.Normal_Tex", STShader::INT, "1"));
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



private:
    Texture* texture;
    Shader* shader;
    Vector3<stReal> m_baseColor;
    bool useTexture;
    std::vector<STShader::ShaderAttrib> _uniforms;
};

#endif //WAHOO_STMATERIAL_H
