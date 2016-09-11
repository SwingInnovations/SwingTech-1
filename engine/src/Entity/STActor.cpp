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
    m_visible = true;
}

STActor::STActor(const std::string &filePath, STMaterial *material) {
    m_transform = new Transform();
    stInt flag = 0;
    std::vector<std::string> tags;
    std::vector<Vector2<stReal>> bounds;
    //TODO - Add something to split up the mesh if there are multiple in the scene.
    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
    addComponent(typeid(STEventComponent), new STEventComponent());
}


void STActor::draw() {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        auto cam = STGame::Get()->getCamera();

        grphx->draw(*m_transform, *cam);
        mesh->draw();
        if(m_children.size() > 0){
            for(auto child : m_children){
                child->draw();
            }
        }
    }
}

