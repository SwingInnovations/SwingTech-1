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
