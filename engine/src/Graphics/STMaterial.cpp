#include "STMaterial.h"
#include "STGraphics.h"
#include "GL/GLTexture.h"
#include "GL/GLShader.h"
#include "../Application/Util/File/STSerializeable.h"

STMaterial::STMaterial() {
    shader = nullptr;
    m_renderMode = OPAQUE;
}

STMaterial::STMaterial(ShaderList shaders, TextureList textures) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        init_GLShaders(shaders);
        init_GLTextures(textures);
    }
    initBaseUniforms();
    m_renderQueue = 3000;
}

STMaterial::STMaterial(Shader *shdr) {
    shader = shdr;
    initBaseUniforms();
}

void STMaterial::draw(std::map<std::string, STShader::ShaderAttrib> &entityUniforms, Transform &T, STCamera *C) {
    shader->bind();
    shader->update(T, C);
    shader->updateUniforms(entityUniforms);
    shader->updateUniforms(m_Uniforms);
}

void STMaterial::draw(std::map<std::string, STShader::ShaderAttrib> &entityUniform,
                      std::map<std::string, STShader::ShaderAttrib> originalMaterialUniforms, Transform &T,
                      STCamera *C) {
    shader->bind();
    shader->update(T, C);
    shader->updateUniforms(entityUniform);
    shader->updateUniforms(originalMaterialUniforms);
}



void STMaterial::setMetallic(stReal value) {
    auto vec = STShader::toVector2(m_Uniforms.at("Material.Metallic").value);
    vec.setX(value);
    m_Uniforms.at("Material.Metallic").value = STShader::toString(vec);
}

void STMaterial::setMetallic(const std::string &fileName) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        if(m_Uniforms.count("Material.Metallic_Tex") > 0){
            //TODO Implement this
        }else{
            m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Metallic_Tex", STShader::ShaderAttrib("Material.Metallic_Tex", STShader::TEX, STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 3)))));
            m_pathReferences["Material.Metallic_Tex"] = fileName;
        }
        if(m_Uniforms.count("Material.Metallic") > 0){
            m_Uniforms.at("Material.Metallic").value = STShader::toString(Vector2<stReal>(0.f, 0.f));
        }
    }
}

void STMaterial::setRoughness(stReal value) {
    auto vec = STShader::toVector2(m_Uniforms.at("Material.Roughness").value);
    vec.setX(value);
    m_Uniforms.at("Material.Roughness").value = STShader::toString(vec);
}

void STMaterial::setRoughness(const std::string &fileName) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        if(m_Uniforms.count("Material.Roughness_Tex") > 0){
            //TODO Proper cleanup and swap of textures
        }else{
            m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Roughness_Tex", STShader::ShaderAttrib("Material.Roughness_Tex", STShader::TEX, STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 4)))));
            m_pathReferences["Material.Roughness_Tex"] = fileName;
        }
        if(m_Uniforms.count("Material.Roughness") > 0){
            m_Uniforms.at("Material.Roughness").value = STShader::toString(Vector2<stReal>(0.f, 0.f));
        }
    }
}

void STMaterial::setDiffuseTexture(const std::string &fileName) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        //Proper way for modifying map.
        if(m_Uniforms.count("Material.Diffuse_Tex") > 0){
            auto textureHandle = (stUint)STShader::toVector2(m_Uniforms.at("Material.Diffuse_Tex").value).getX();
            glDeleteTextures(0, &textureHandle);
            m_Uniforms.at("Material.Diffuse_Tex").value = STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 2));
            m_pathReferences["Material.Diffuse_Tex"] = fileName;
        }else{
            m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Diffuse_Tex", STShader::ShaderAttrib("Material.Diffuse_Tex", STShader::TEX, STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 2)))));
            m_pathReferences["Material.Diffuse_Tex"] = fileName;
        }
        if(m_Uniforms.count("Material.Diffuse_Color") > 0)
            m_Uniforms.at("Material.Diffuse_Color").value = STShader::toString(Vector4<stReal>(0.f, 0.f, 0.f, -1.0f));
    }

}

void STMaterial::setNormalTexture(const std::string &fileName) {
    if(m_Uniforms.count("Material.Normal_Tex") > 0){
        //TODO Implement some way of swapping the textures.
    }else{
        m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Normal_Tex", STShader::ShaderAttrib("Material.Normal_Tex", STShader::TEX, STShader::toString(Vector2<stInt>(GLTexture::GenTex(fileName), 3)))));
        m_pathReferences["Material.Normal_Tex"] = fileName;
    }
    if(m_Uniforms.count("Material.Normal_Use") > 0) m_Uniforms.at("Material.Normal_Use").value = std::to_string(1);
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
    if(m_Uniforms.count("Material.Diffuse_Color") > 0) m_Uniforms.at("Material.Diffuse_Color").value = STShader::toString(color.color);
}

void STMaterial::setDiffuseColor(Vector4D color) {
    if(m_Uniforms.count("Material.Diffuse_Color") > 0) m_Uniforms.at("Material.Diffuse_Color").value = STShader::toString(color);
}


STMaterial *STMaterial::copy() {
    STMaterial* ret = new STMaterial(shader);
    ret->setUniforms(m_Uniforms);
    return ret;
}

void STMaterial::setUniforms(std::map<std::string, STShader::ShaderAttrib> newUniforms) {
    m_Uniforms = newUniforms;
}

void STMaterial::save(std::ofstream &out) {
    shader->save(out);
    auto refCount = (stUint)m_pathReferences.size();
    out.write((char*)&refCount, sizeof(stUint));
    for(auto ref : m_pathReferences){
        STSerializableUtility::WriteString(ref.first.c_str(), out);
        STSerializableUtility::WriteString(ref.second.c_str(), out);
    }
    auto uniformcount = (stUint)m_Uniforms.size();
    out.write((char*)&uniformcount, sizeof(stUint));
    for(auto uniform : m_Uniforms){
        STSerializableUtility::WriteString(uniform.first.c_str(), out);
        uniform.second.save(out);
    }
}

void STMaterial::load(std::ifstream &in) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        shader = new GLShader();
        shader->load(in);
    }
    if(shader){
        stUint refCount, uniformCount;
        in.read((char*)&refCount, sizeof(stUint));
        for(stUint i = 0; i < refCount; i++){
            std::string key = STSerializableUtility::ReadString(in);
            std::string value = STSerializableUtility::ReadString(in);
            m_pathReferences[key] = value;
        }

        in.read((char*)&uniformCount, sizeof(stUint));
        for(stUint i = 0; i < uniformCount; i++) {
            std::string key = STSerializableUtility::ReadString(in);
            STShader::ShaderAttrib shaderAttrib;
            shaderAttrib.load(in);
            m_Uniforms[key] = shaderAttrib;
        }

        for(auto ref : m_pathReferences){
            auto oldTextureIndex = STShader::toVector2(m_Uniforms[ref.first].value).getY();
            m_Uniforms[ref.first] = STShader::ShaderAttrib(ref.first, STShader::TEX, STShader::toString(Vector2<stInt>(GLTexture::GenTex(ref.second), (stInt)oldTextureIndex)));
        }
    }
}

STMaterial::~STMaterial() {
    delete shader;
    for(auto uniform : m_Uniforms){
        if(uniform.second.type == STShader::TEX){
            auto texHandle = (stUint)STShader::toVector2(uniform.second.value).getX();
            glDeleteTextures(1, &texHandle);
        }
    }
}

stUint STMaterial::getRenderQueue() const {
    return m_renderQueue;
}

void STMaterial::setRenderQueue(stUint value) {
    m_renderQueue = value;
}

void STMaterial::setRenderMode(STMaterial::RenderMode renderMode) {
    m_renderMode = renderMode;
}

STMaterial::RenderMode STMaterial::getRenderMode() const {
    return m_renderMode;
}




