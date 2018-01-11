#include "STGraphicsComponent.h"
#include "../STEntity.h"
#include "../../Graphics/GL/GLShader.h"
#include "../../Graphics/STGraphics.h"

STGraphicsComponent::STGraphicsComponent(const STGraphicsComponent &copy) {
    this->m_entity = copy.m_entity;
}

STGraphicsComponent::STGraphicsComponent(Shader *shdr) {
    useTexture = false;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(const std::string &shdr) {
    useTexture = false;
    useMaterial = false;
}

STGraphicsComponent::STGraphicsComponent(STMaterial *mat) {
    useMaterial = true;
}

STGraphicsComponent::STGraphicsComponent(std::shared_ptr<STMaterial> material) {
    //TODO Implement this
    m_Material = material;
}

void STGraphicsComponent::addShdrUniform(const std::string &name, int value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::INT, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform(name, value);
    }
}

void STGraphicsComponent::addShdrUniform(const std::string &name, float value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::FLOAT, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform(name, value);
    }
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector2<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC2, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform(name, value);
    }
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector3<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC3, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform(name, value);
    }
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Vector4<stReal> value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::VEC4, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform(name, value);
    }
}

void STGraphicsComponent::addShdrUniform(const std::string &name, Matrix4f value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::MAT4, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform(name, value);
    }
}

void STGraphicsComponent::addShdrUniform_Texture(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform_Texture(name, value);
    }
}

void STGraphicsComponent::addShdrUniform_Texture2DArray(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0)m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX2DARR, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform_Texture2DArray(name, value);
    }
}

void STGraphicsComponent::addShdrUniform_CubeMap(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) == 0) m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::CUBE_MAP, STShader::toString(value))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->addShdrUniform_CubeMap(name, value);
    }
}

void STGraphicsComponent::setShdrUniform(const std::string &name, int value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);

    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform(name, value);
    }
}

void STGraphicsComponent::setShdrUniform(const std::string &name, float value) {
    if(m_Uniforms.count(name) > 0)m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform(name, value);
    }
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector2<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform(name, value);
    }
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector3<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform(name, value);
    }
}

void STGraphicsComponent::setShdrUniform(const std::string &name, Vector4<stReal> value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform(name, value);
    }
}

void STGraphicsComponent::setShdrUniform_Texture(const std::string &name, stUint id, stUint index) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(Vector2<stInt>(id, index));
    else m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(Vector2<stInt>(id, index)))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform_Texture(name, id, index);
    }
}


void STGraphicsComponent::setShdrUniform(const std::string &name, Matrix4f value) {
    if(m_Uniforms.count(name) > 0)m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform(name, value);
    }
}

void STGraphicsComponent::setShdrUniform_Texture(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform_Texture(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform_Texture(name, value);
    }
}

void STGraphicsComponent::setShdrUniform_Texture2DArray(const std::string &name, stUint id, stUint index) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(Vector2<stInt>(id, index));
    else m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>(name, STShader::ShaderAttrib(name, STShader::TEX, STShader::toString(Vector2<stInt>(id, index)))));
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform_Texture2DArray(name, id, index);
    }
}

void STGraphicsComponent::setShdrUniform_CubeMap(const std::string &name, stUint value) {
    if(m_Uniforms.count(name) > 0) m_Uniforms.at(name).value = STShader::toString(value);
    else addShdrUniform_CubeMap(name, value);
    for(auto child : m_entity->getChildren()){
        child->get<STGraphicsComponent>()->setShdrUniform_CubeMap(name, value);
    }
}

void STGraphicsComponent::update() {

}

void STGraphicsComponent::draw(Transform &T, Camera &C) {
    //m_material->draw(m_Uniforms, T, C);
    m_Material->draw(m_Uniforms, T, C);
}

void STGraphicsComponent::setDiffuseTexture(const std::string &fileName) {
    m_Material->setDiffuseTexture(fileName);
}

void STGraphicsComponent::setNormalTexture(const std::string &fileName) {
    m_Material->setNormalTexture(fileName);
}

std::map<std::string, STShader::ShaderAttrib> &STGraphicsComponent::GetUniforms() {
    return m_Uniforms;
}

void STGraphicsComponent::draw() {
    //m_material->draw(m_uniforms);
    //m_material->draw();
}

void STGraphicsComponent::dispose() {
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

void STGraphicsComponent::initScriptingFunctions(sol::state &state) {
    state.set_function("getGraphicsComponent", [](STEntity* self){
        return self->get<STGraphicsComponent>();
    });

    state.new_simple_usertype<STMaterial>("STMaterial",
                                        "setRoughness", sol::resolve<void(const std::string&)>(&STMaterial::setRoughness),
                                        "setMetallic", sol::resolve<void(const std::string&)>(&STMaterial::setMetallic),
                                        "setRoughnessF", sol::resolve<void(float)>(&STMaterial::setRoughness),
                                        "setMetallicF", sol::resolve<void(float)>(&STMaterial::setMetallic),
                                        "setDiffuseColor", sol::resolve<void(Vector4D)>(&STMaterial::setDiffuseColor),
                                        "setDiffuseTexture", sol::resolve<void(const std::string&)>(&STMaterial::setDiffuseTexture),
                                        "setNormalTexture", sol::resolve<void(const std::string&)>(&STMaterial::setNormalTexture));

    state.new_simple_usertype<STGraphicsComponent>("STGraphicsComponent",
                                                   "addShdrUniformi", sol::resolve<void(const std::string&, int)>(&STGraphicsComponent::addShdrUniform),
                                                   "addShdrUniformf", sol::resolve<void(const std::string&, float)>(&STGraphicsComponent::addShdrUniform),
                                                   "addShdrUniform2v", sol::resolve<void(const std::string&, Vector2D)>(&STGraphicsComponent::addShdrUniform),
                                                   "addShdrUniform3v", sol::resolve<void(const std::string&, Vector3D)>(&STGraphicsComponent::addShdrUniform),
                                                   "addShdrUniform4v", sol::resolve<void(const std::string&, Vector4D)>(&STGraphicsComponent::addShdrUniform),
                                                   "setShdrUniformi", sol::resolve<void(const std::string&, int)>(&STGraphicsComponent::setShdrUniform),
                                                   "setShdrUniformf", sol::resolve<void(const std::string&, float)>(&STGraphicsComponent::setShdrUniform),
                                                   "setShdrUniform2v", sol::resolve<void(const std::string&, Vector2D)>(&STGraphicsComponent::setShdrUniform),
                                                   "setShdrUniform3v", sol::resolve<void(const std::string&, Vector3D)>(&STGraphicsComponent::setShdrUniform),
                                                   "setShdrUniform4v", sol::resolve<void(const std::string&, Vector4D)>(&STGraphicsComponent::setShdrUniform),
                                                   "getMaterial", &STGraphicsComponent::getMaterial);
}

template<class Archive>
void STGraphicsComponent::serialize(Archive &ar) {
    ar(m_Material);
}




