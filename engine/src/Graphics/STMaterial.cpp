#include "STMaterial.h"
#include "STGraphics.h"
#include "GL/GLTexture.h"

STMaterial::STMaterial() {
    shader = nullptr;
    texture = nullptr;
}

STMaterial::STMaterial(ShaderList shaders, TextureList textures) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        init_GLShaders(shaders);
        init_GLTextures(textures);
    }
    initBaseUniforms();
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
}

void STMaterial::draw(std::vector<STShader::ShaderAttrib> &entityUniforms, std::vector<STShader::ShaderAttrib> originalMaterialUniforms, Transform &T, Camera &C) {
    shader->bind();
    shader->update(T, C);
    shader->updateUniforms(entityUniforms);
    shader->updateUniforms(originalMaterialUniforms);
    //shader->updateUniforms(_uniforms);
}

void STMaterial::setDiffuseTexture(const std::string &fileName) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        _uniforms.push_back(STShader::ShaderAttrib("Material.Diffuse_Tex",
                                                   STShader::TEX,
                                                   STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 2))));
        for(stUint i = 0, S = _uniforms.size(); i < S; i++){
            if(_uniforms[i].name == "Material.Diffuse_Color"){
                _uniforms[i].value = STShader::toString(Vector4<stReal>(0.f, 0.f, 0.f, -1.f));
            }
        }
    }

}

void STMaterial::setNormalTexture(const std::string &fileName) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        _uniforms.push_back(STShader::ShaderAttrib("Material.Normal_Tex",
                                                   STShader::TEX,
                                                   STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 3))));
    }

}

void STMaterial::init_GLShaders(ShaderList list) {
    if(!list.vertShader.empty()){
        if(!list.fragShader.empty()){
            if(!list.geomShader.empty()){
                std::cout << "Geom Shader exists" << std::endl;
                //TODO Initialize shader with geometry shader.
                return;
            }
            shader = new GLShader(list.vertShader, list.fragShader);
            return;
        }
        shader = new GLShader(list.vertShader);
    }
}

void STMaterial::init_GLTextures(TextureList list) {
    if(!list.diffuseTex.empty())    setDiffuseTexture(list.diffuseTex);
    if(!list.normalTex.empty())     setNormalTexture(list.normalTex);
}

void STMaterial::setDiffuseColor(STColor color) {
    for(stUint i = 0, S = _uniforms.size(); i < S; i++){
        if(_uniforms[i].name == "Material.Diffuse_Color"){
            _uniforms[i].value = STShader::toString(color.color);
        }
    }
}

