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

STEntity::STEntity(const std::string &fileName, const int type, STMaterial *mat) {
    m_transform = new Transform;
    addComponent(typeid(STMeshComponent), new STMeshComponent(fileName, type));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(mat));
}


STEntity::STEntity(STRect *rect,Shader *shdr) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(rect));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdr));
}

STEntity::STEntity(STCube* cube, Shader* shdr){
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(cube));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdr));
}

STEntity::STEntity(STCube* cube, Shader* shdr, Texture* tex){
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(cube));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdr, tex));
}

STEntity::STEntity(STQuad *quad, Shader *shdr) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(quad));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(shdr));
}

STEntity::~STEntity() {
    delete m_transform;
    m_transform = 0;
    m_components.clear();
}

void STEntity::addComponent(std::type_index type, STComponent *component) {
    m_components[type] = component;
}

void STEntity::addChild(STEntity *entity) {
    m_children.push_back(entity);
}

STEntity* STEntity::getChild(int ind) {
    return m_children.at(ind);
}

void STEntity::BtSUpdate(STGame *window, int delta) {
    for (auto& component : m_components) {
        component.second->update(window, delta);
    }
}

void STEntity::setTranslate(Vector3<stReal> &vec) {
    m_transform->setTranslate(vec);
    if(!m_children.empty()){
        for(STEntity* entity : m_children){
            Vector3<stReal> childPosition = entity->transform()->getTranslate<stReal>();
            childPosition = childPosition + vec;
            entity->setTranslate(childPosition);
        }
    }

}

void STEntity::setTranslate(stReal _value){
    m_transform->setTranslate(_value);
    if(!m_children.empty()){
        for(auto entity : m_children){
            Vector3<stReal> childPosition = entity->transform()->getTranslate<stReal>();
            childPosition = childPosition + _value;
            entity->setTranslate(childPosition);
        }
    }

}

void STEntity::setTranslateX(stReal _x) {
    m_transform->setTranslateX(_x);
    if(!m_children.empty()){
        for(auto entity : m_children){
            stReal cX = entity->transform()->getTranslate<stReal>().getX();
            cX += _x;
            entity->setTranslateX(_x);
        }
    }

}

void STEntity::setTranslateY(stReal _y) {
    m_transform->setTranslateY(_y);
    if(!m_children.empty()){
        for(auto entity : m_children){
            stReal cY = entity->transform()->getTranslate<stReal>().getY();
            cY += _y;
            entity->setTranslateY(_y);
        }
    }

}

void STEntity::setTranslateZ(stReal _z){
    m_transform->setTranslateZ(_z);
    if(!m_children.empty()){
        for(auto entity : m_children){
            stReal cZ = entity->transform()->getTranslate<stReal>().getZ();
            cZ += _z;
            entity->setTranslateZ(_z);
        }
    }
}

void STEntity::setRotate(Vector3<stReal> &vec) {
    m_transform->setRotate(vec);
}

void STEntity::setRotateX(stReal _x) {
    m_transform->setRotateX(_x);
}

void STEntity::setRotateY(stReal _y){
    m_transform->setRotateY(_y);
}

void STEntity::setRotateZ(stReal _z) {
    m_transform->setTranslateZ(_z);
}


void STEntity::setScale(Vector3<stReal> &vec) {
    m_transform->setScale(vec);
}

void STEntity::setScale(stReal _value) {
    m_transform->setScale(_value);
}

void STEntity::setScaleX(stReal _x) {
    m_transform->setScale(_x);
}

void STEntity::setScaleY(stReal _y) {
    m_transform->setScaleY(_y);
}

void STEntity::setScaleZ(stReal _z) {
    m_transform->setScaleZ(_z);
}

void STEntity::addShdrUniform(const std::string &name, int value) {
    get<STGraphicsComponent>()->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string &name, float value) {
    get<STGraphicsComponent>()->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string& name, Vector3<stReal> value){
    get<STGraphicsComponent>()->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string &name, Vector4<stReal> value) {
    get<STGraphicsComponent>()->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name,int value) {
    get<STGraphicsComponent>()->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, float value) {
    get<STGraphicsComponent>()->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, Vector3<stReal> value) {
    get<STGraphicsComponent>()->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, Vector4<stReal> value) {
    get<STGraphicsComponent>()->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

STEntity *STEntity::childAtTag(const std::string &tag) {
    return nullptr;
}
