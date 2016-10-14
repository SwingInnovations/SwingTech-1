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
    }

    ~STMaterial(){
        delete texture;
        delete shader;
    }

    /*!
     * @param fileName Adds diffuse texture and assigns to texture index 0
     */
    inline void addDiffuse(const std::string& fileName){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.diffuse", STShader::INT, "0"));
        texture->addTexture(fileName, 0);
    }

    /*!
     *
     * @param diffuse Adds diffuse texture and assigns to texture index 0
     */
    inline void addDiffuse(Vector3<stReal> diffuse){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.diffuse", STShader::VEC3, STShader::toString(diffuse)));
    }

    /*!
     *
     * @param fileName Adds Specular map and assigns to texture index 1
     */
    inline void addSpecular(const std::string& fileName){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.diffuse", STShader::INT, "1"));
        texture->addTexture(fileName, 1);
    }

    /*!
     *
     * @param specular Adds Specular map and assigns to texture index 1
     */
    inline void addSpecular(Vector3<stReal> specular){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.specular", STShader::VEC3, STShader::toString(specular)));
    }
    inline void addNormal(Vector3<stReal> normal){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.normal", STShader::VEC3, STShader::toString(normal)));
    }

    inline void addNormal(const std::string& fileName){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.normal", STShader::INT, "2"));
        texture->addTexture(fileName, 2);
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

    void draw(std::vector<STShader::ShaderAttrib>& entityUniforms);

    void draw(std::vector<STShader::ShaderAttrib>& entityUniforms, Transform& T, Camera& C);
private:
    Texture* texture;
    Shader* shader;
    bool useTexture;
    std::vector<STShader::ShaderAttrib> _uniforms;
};

#endif //WAHOO_STMATERIAL_H
