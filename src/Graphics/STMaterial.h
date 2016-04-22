#ifndef WAHOO_STMATERIAL_H
#define WAHOO_STMATERIAL_H

#include <vector>

#include "Texture.h"
#include "Shader.h"
#include "GL/GLTexture.h"

class STMaterial{
public:
    STMaterial(){

    }

    STMaterial(Shader* shdr){
        shader = shdr;
        texture = new Texture();
    }

    STMaterial(Shader* shdr, Texture* tex){
        shader = shdr;
        texture = tex;
    }

    ~STMaterial(){
        delete texture;
        delete shader;
    }

    void addDiffuse(const std::string& fileName){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.diffuse", STShader::INT, "0"));
        texture->addTexture(fileName, 0);
    }

    void addDiffuse(Vector3<stReal> diffuse){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.diffuse", STShader::VEC3, STShader::toString(diffuse)));
    }

    void addSpecular(const std::string& fileName){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.diffuse", STShader::INT, "1"));
        texture->addTexture(fileName, 1);
    }

    void addSpecular(Vector3<stReal> specular){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.specular", STShader::VEC3, STShader::toString(specular)));
    }
    void addNormal(Vector3<stReal> normal){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.normal", STShader::VEC3, STShader::toString(normal)));
    }
    void addNormal(const std::string& fileName){
        _uniforms.push_back(STShader::ShaderAttrib("STMaterial.normal", STShader::INT, "2"));
        texture->addTexture(fileName, 2);
    }

    void update(){
        shader->bind();
        shader->updateUniforms(_uniforms);
        for(unsigned int i = 0; i < texture->getTextureCount(); i++){
            texture->bind(i);
        }
    }

    Shader* shdr(){ return shader; }

    void update(std::vector<STShader::ShaderAttrib> entityUniforms){
        shader->bind();
        shader->updateUniforms(_uniforms);
        shader->updateUniforms(entityUniforms);
        if(texture->getTextureCount() > 31){
            texture->bind(0);
            std::cout << "Using Texture Fallback Mode" << std::endl;
        }else{
            for(unsigned int i = 0, S = texture->getTextureCount(); i < S; i++){
                texture->bind(i);
            }
        }

    }
private:
    Texture* texture;
    Shader* shader;
    bool useTexture;
    std::vector<STShader::ShaderAttrib> _uniforms;
};

#endif //WAHOO_STMATERIAL_H
