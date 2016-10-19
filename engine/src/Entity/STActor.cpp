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

STActor::STActor(const std::string &filePath, const int type, std::string &tag, Vector2<stInt> bounds,
                 Vector3<stInt> maxSizes, STMaterial *material) {
    m_transform = new Transform;
    m_tag = tag;
    m_type = Actor;
    m_visible = true;
    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath, type, bounds, maxSizes));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
    addComponent(typeid(STEventComponent), new STEventComponent);
}

/**
 * Creates a new Actor Entity based on file path and material.
 * If multiple meshes are present in the file, then they will be added as children.
 * @param filePath Input File Path.
 * @param material Material to be applied to actor.
 */
STActor::STActor(const std::string &filePath, STMaterial *material) {
    m_transform = new Transform();
    m_type = Actor;
    m_visible = true;
    stInt flag = 0;
    std::vector<std::string> tags;
    std::vector<Vector2<stInt>> bounds;
    std::vector<Vector3<stInt>> maxSizes; //Keeps track of the largest vertices.
    maxSizes.push_back(Vector3<stInt>(0, 0, 0));
    addComponent(typeid(STEventComponent), new STEventComponent());

    if(STMesh::Validate(filePath, &flag, &tags, &bounds, &maxSizes)){
        if(tags.size() < bounds.size()){
            for(unsigned int i = 0, N = bounds.size(); i < N; i++){
                tags.clear();
                std::string tag = "child";
                tags.push_back(tag);
            }
        }
        for(stInt i = 0, boundSize = (stInt)bounds.size(); i < boundSize; i++){
            this->addChild_Actor( new STActor(filePath, flag, tags.at(i), bounds.at(i), maxSizes.at(i), material));
        }
        return;
    }

    if(tags.size() > 0)
        m_tag = tags.at(0);
    else m_tag = "Actor";
    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath, flag));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
}

//TODO - Implement draw using specified material.

void STActor::draw() {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        auto cam = STGame::Get()->getCamera();

        if(grphx != nullptr)grphx->draw(*m_transform, *cam);
        if(mesh != nullptr)mesh->draw();
        for(auto child : m_children){
            dynamic_cast<STActor*>(child)->draw(cam, 2);
        }
    }
}

void STActor::draw(Camera *camera, int drawMode) {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        grphx->draw(*m_transform, *camera);
        mesh->draw(drawMode);
    }
}

void STActor::draw(STMaterial *material) {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        auto cam = STGame::Get()->getCamera();
        auto uniforms = grphx->getMaterial()->getUniforms();
        material->draw(grphx->getMaterial()->getUniforms(), *m_transform, *cam);
        mesh->draw();
    }
}
