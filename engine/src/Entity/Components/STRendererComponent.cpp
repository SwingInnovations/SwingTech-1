#include "STRendererComponent.h"
#include "../STEntity.h"
#include "../../Graphics/GL/GLShader.h"
#include "../../Graphics/STGraphics.h"

STRendererComponent::STRendererComponent() {

}

STRendererComponent::STRendererComponent(const STRendererComponent &copy) {
    this->m_entity = copy.m_entity;
}

STRendererComponent::STRendererComponent(std::shared_ptr<STMaterial> material) {
    //TODO Implement this
    m_Material = material;
}

void STRendererComponent::addShdrUniform(const std::string &name, int value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::INT, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform(name, value);
    }
}

void STRendererComponent::addShdrUniform(const std::string &name, float value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::FLOAT, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform(name, value);
    }
}

void STRendererComponent::addShdrUniform(const std::string &name, Vector2<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC2, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform(name, value);
    }
}

void STRendererComponent::addShdrUniform(const std::string &name, Vector3<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC3, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform(name, value);
    }
}

void STRendererComponent::addShdrUniform(const std::string &name, Vector4<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC4, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform(name, value);
    }
}

void STRendererComponent::addShdrUniform(const std::string &name, Matrix4f value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::MAT4, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform(name, value);
    }
}

void STRendererComponent::addShdrUniform_Texture(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform_Texture(name, value);
    }
}

void STRendererComponent::addShdrUniform_Texture2DArray(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX2DARR, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform_Texture2DArray(name, value);
    }
}

void STRendererComponent::addShdrUniform_CubeMap(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0) m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::CUBE_MAP, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->addShdrUniform_CubeMap(name, value);
    }
}

void STRendererComponent::setShdrUniform(const std::string &name, int value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);

    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform(name, value);
    }
}

void STRendererComponent::setShdrUniform(const std::string &name, float value) {
    if(m_Uniforms.count(name) > 0)m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform(name, value);
    }
}

void STRendererComponent::setShdrUniform(const std::string &name, Vector2<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform(name, value);
    }
}

void STRendererComponent::setShdrUniform(const std::string &name, Vector3<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform(name, value);
    }
}

void STRendererComponent::setShdrUniform(const std::string &name, Vector4<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform(name, value);
    }
}

void STRendererComponent::setShdrUniform_Texture(const std::string &name, stUint id, stUint index) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(Vector2<stInt>(id, index));
    else m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(Vector2<stInt>(id, index)))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform_Texture(name, id, index);
    }
}


void STRendererComponent::setShdrUniform(const std::string &name, Matrix4f value) {
    if(m_Uniforms.count(name) > 0)m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform(name, value);
    }
}

void STRendererComponent::setShdrUniform_Texture(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform_Texture(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform_Texture(name, value);
    }
}

void STRendererComponent::setShdrUniform_Texture2DArray(const std::string &name, stUint id, stUint index) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(Vector2<stInt>(id, index));
    else m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(Vector2<stInt>(id, index)))));
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform_Texture2DArray(name, id, index);
    }
}

void STRendererComponent::setShdrUniform_CubeMap(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform_CubeMap(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STRendererComponent>()->setShdrUniform_CubeMap(name, value);
    }
}

void STRendererComponent::update() {

}

void STRendererComponent::draw(Transform &T, Camera &C) {
    //m_material->draw(m_Uniforms, T, C);
    m_Material->draw(m_Uniforms, T, C);
}

void STRendererComponent::setDiffuseTexture(const std::string &fileName) {
    m_Material->setDiffuseTexture(fileName);
}

void STRendererComponent::setNormalTexture(const std::string &fileName) {
    m_Material->setNormalTexture(fileName);
}

std::map<std::string, STShader::ShaderAttrib> &STRendererComponent::GetUniforms() {
    return m_Uniforms;
}

void STRendererComponent::draw() {
    //m_material->draw(m_uniforms);
    //m_material->draw();
}

void STRendererComponent::dispose() {
    for(auto uniform : m_Uniforms){
        if(uniform.second.type == STShader::TEX){
            if(STGraphics::RENDERER == STGraphics::OPENGL){
                auto texHandle = (stUint)STShader::toVector2(uniform.second.value).getX();
                GLTexture::DisposeTex(texHandle);
            }
        }
    }
    m_Material.reset();
}

void STRendererComponent::initScriptingFunctions(sol::state &state) {
    state.set_function("GetRendererComponent", [](STEntity* self){
        return self->get<STRendererComponent>();
    });

    state.new_simple_usertype<STMaterial>("STMaterial",
                                        "setRoughness", sol::resolve<void(const std::string&)>(&STMaterial::setRoughness),
                                        "setMetallic", sol::resolve<void(const std::string&)>(&STMaterial::setMetallic),
                                        "setRoughnessF", sol::resolve<void(float)>(&STMaterial::setRoughness),
                                        "setMetallicF", sol::resolve<void(float)>(&STMaterial::setMetallic),
                                        "setDiffuseColor", sol::resolve<void(Vector4D)>(&STMaterial::setDiffuseColor),
                                        "setDiffuseTexture", sol::resolve<void(const std::string&)>(&STMaterial::setDiffuseTexture),
                                        "setNormalTexture", sol::resolve<void(const std::string&)>(&STMaterial::setNormalTexture));

    state.new_simple_usertype<STRendererComponent>("STRendererComponent",
                                                   "addShdrUniformi", sol::resolve<void(const std::string&, int)>(&STRendererComponent::addShdrUniform),
                                                   "addShdrUniformf", sol::resolve<void(const std::string&, float)>(&STRendererComponent::addShdrUniform),
                                                   "addShdrUniform2v", sol::resolve<void(const std::string&, Vector2D)>(&STRendererComponent::addShdrUniform),
                                                   "addShdrUniform3v", sol::resolve<void(const std::string&, Vector3D)>(&STRendererComponent::addShdrUniform),
                                                   "addShdrUniform4v", sol::resolve<void(const std::string&, Vector4D)>(&STRendererComponent::addShdrUniform),
                                                   "setShdrUniformi", sol::resolve<void(const std::string&, int)>(&STRendererComponent::setShdrUniform),
                                                   "setShdrUniformf", sol::resolve<void(const std::string&, float)>(&STRendererComponent::setShdrUniform),
                                                   "setShdrUniform2v", sol::resolve<void(const std::string&, Vector2D)>(&STRendererComponent::setShdrUniform),
                                                   "setShdrUniform3v", sol::resolve<void(const std::string&, Vector3D)>(&STRendererComponent::setShdrUniform),
                                                   "setShdrUniform4v", sol::resolve<void(const std::string&, Vector4D)>(&STRendererComponent::setShdrUniform),
                                                   "getMaterial", &STRendererComponent::getMaterial);
}

void STRendererComponent::save(std::ofstream &out) {
    m_Material->save(out);
}

void STRendererComponent::load(std::ifstream &in) {
    m_Material = std::make_shared<STMaterial>();
    m_Material->load(in);
}

STRendererComponent::STRendererComponent(Shader *shdr) {

}



