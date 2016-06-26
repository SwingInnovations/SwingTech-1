//
// Created by NDanq on 6/25/2016.
//

#include "STActor.h"
#include "Components/STEventComponent.h"

STActor::STActor(const std::string &filePath, const int type, STMaterial *material) {
    m_transform = new Transform();
    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath, type));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
    addComponent(typeid(STEventComponent), new STEventComponent());
}

void STActor::draw() {
    auto mesh = this->get<STMeshComponent>();
    auto grphx = this->get<STGraphicsComponent>();

    grphx->draw();
    mesh->draw();
    if(m_children.size() > 0){
        for(auto child : m_children){
            child->draw();
        }
    }
}
