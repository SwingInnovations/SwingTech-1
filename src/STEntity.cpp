#include "STEntity.h"

STEntity::STEntity() {
    m_transform = new Transform();
}

STEntity::STEntity(const std::string &fileName, const int type, Shader *shdr) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(fileName, type));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdr));
}

STEntity::STEntity(const std::string &fileName, const int type, Shader *shdr, Texture *tex) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(fileName, type));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdr, tex));
}

STEntity::STEntity(const std::string &fileName, const int type, const std::string &shdrPath) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(fileName, type));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdrPath));
}

STEntity::STEntity(const std::string &fileName, const int type, const std::string &shdrPath,
                   const std::string texPath) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(fileName, type));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdrPath, texPath));
}

STEntity::STEntity(SWRect *rect, const std::string &shdrPath) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(rect));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdrPath));
}

STEntity::STEntity(SWRect *rect, Shader *shdr) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(rect));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdr)));
}

STEntity::~STEntity() {
    delete m_transform;
    m_transform = 0;
    m_components.clear();
}

void STEntity::addComponent(std::type_index type, STComponent *component) {
    m_components[type] = component;
}

void STEntity::BtSUpdate(STGame *window, int delta) {
    for (auto& component : m_components) {
        component.second->update(window, delta);
    }
}