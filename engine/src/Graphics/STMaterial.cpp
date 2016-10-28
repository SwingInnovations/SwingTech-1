#include "STMaterial.h"
#include "STGraphics.h"
#include "GL/GLTexture.h"

STMaterial::STMaterial() {
    shader = nullptr;
    texture = nullptr;
}

STMaterial::STMaterial(Shader *shdr) {
    shader = shdr;
    if(STGraphics::RENDERER == STGraphics::OPENGL) texture = new GLTexture();
    initBaseUniforms();
}

void STMaterial::draw(std::vector<STShader::ShaderAttrib> &entityUniforms,Transform &T, Camera &C) {
    shader->bind();
    shader->update(T, C);
    shader->updateUniforms(entityUniforms);
    shader->updateUniforms(_uniforms);
    if(texture->getTextureCount() > 31){
        texture->bind(0);
    }else{
        for(stUint i = 0, S = texture->getTextureCount(); i < S; i++){
            texture->bind(i);
        }
    }
}


void STMaterial::draw(std::vector<STShader::ShaderAttrib> &entityUniforms, Texture *passTexture, Transform &T, Camera &C) {
//    shader->bind();
//    shader->update(T, C);
//    shader->updateUniforms(entityUniforms);
//    shader->updateUniforms(_uniforms);
//    auto texCount = passTexture->getTextureCount();
//    passTexture->bind(0);
//    passTexture->bind(1);
//    if(passTexture->getTextureCount() > 31){
//        passTexture->bind(0);
//    }else{
//        for(stUint i = 0, S = passTexture->getTextureCount(); i < S; i++){
//            passTexture->bind(i);
//        }
//    }
}

void STMaterial::setDiffuseTexture(const std::string &fileName) {
    //texture->addTexture(fileName, 0);
    _uniforms.push_back(STShader::ShaderAttrib("Material.Diffuse_Tex",
                                               STShader::TEX,
                                               STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 1))));
}

void STMaterial::setNormalTexture(const std::string &fileName) {
    _uniforms.push_back(STShader::ShaderAttrib("Material.Normal_Tex",
                                               STShader::TEX,
                                               STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 2))));

}
