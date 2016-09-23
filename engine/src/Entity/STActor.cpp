//
// Created by NDanq on 6/25/2016.
//

#include "STActor.h"
#include "Components/STEventComponent.h"

STActor::STActor(const std::string &filePath, const int type, STMaterial *material) {
    m_transform = new Transform();
    m_type = Actor;
    m_visible = true;
    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath, type));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
    addComponent(typeid(STEventComponent), new STEventComponent());
    m_visible = true;
}

STActor::STActor(const std::string &filePath, const int type, std::string& tag, Vector2<stInt> bounds,
                 STMaterial *material) {
    m_transform = new Transform;
    m_tag = tag;
    m_type = Actor;
    m_visible = true;
    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath, type, bounds));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
    addComponent(typeid(STEventComponent), new STEventComponent);
}

STActor::STActor(const std::string &filePath, STMaterial *material) {
    m_transform = new Transform();
    m_type = Actor;
    m_visible = true;
    stInt flag = 0;
    std::vector<std::string> tags;
    std::vector<Vector2<stInt>> bounds;
    addComponent(typeid(STEventComponent), new STEventComponent());

    if(STMesh::Validate(filePath, &flag, &tags, &bounds)){
        if(tags.size() < bounds.size()){
            for(unsigned int i = 0, N = bounds.size(); i < N; i++){
                tags.clear();
                std::string tag = "child";
                tags.push_back(tag);
            }
        }
        for(stInt i = 0, boundSize = (stInt)bounds.size(); i < boundSize; i++){
            this->addChild_Actor( new STActor(filePath, flag, tags.at(0), bounds.at(i), material));
        }
        return;
    }

    if(tags.size() > 0) m_tag = tags.at(0);
    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath, flag));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
}


void STActor::draw() {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        auto cam = STGame::Get()->getCamera();

        if(grphx != nullptr)grphx->draw(*m_transform, *cam);
        if(mesh != nullptr)mesh->draw();
        if(m_children.size() > 0){
            for(auto child : m_children){
                child->draw();
            }
        }
    }
}

