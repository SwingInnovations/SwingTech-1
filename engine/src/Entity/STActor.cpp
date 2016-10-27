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

STActor::STActor(STMesh_Structure structure, std::string &tag, STMaterial* material) {
    m_transform = new Transform;
    m_tag = tag;
    m_type = Actor;
    m_visible = true;
    addComponent(typeid(STMeshComponent), new STMeshComponent(structure));
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
    bool errFlag = true;
    std::vector<std::string> tags;
    std::vector<STMesh_Structure> meshes;
    addComponent(typeid(STEventComponent), new STEventComponent());

    if(STMesh::Validate(filePath, &errFlag, &tags, &meshes)){
        for(stUint i = 0, S = meshes.size(); i < S; i++){
            this->addChild_Actor(new STActor(meshes.at(i), tags.at(i), material));
        }
        return;
    }else{
        if(!errFlag){
            //TODO Add error mesh.
            addComponent(typeid(STMeshComponent), new STMeshComponent("base/ErrorMesh.obj", STMesh::OBJ));
            addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(new GLShader("base/errorObject"))));
            get<STEventComponent>()->updateEvent([](STEntity* self){
                auto grphx = self->get<STGraphicsComponent>();
                grphx->setShdrUniform("intensity", (stReal)sin(STGame::Get()->getTick() * 0.01f));
            });
            this->transform()->setRotateY(180.0f);
            return;
        }
        addComponent(typeid(STMeshComponent), new STMeshComponent(meshes.at(0)));
        addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
    }

    if(tags.size() > 0)
        m_tag = tags.at(0);
    else m_tag = "Actor";

}

void STActor::draw() {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        auto cam = STGame::Get()->getCamera();

        if(grphx != nullptr)grphx->draw(*m_transform, *cam);
        if(mesh != nullptr)mesh->draw();
        for(auto child : m_children){
            dynamic_cast<STActor*>(child)->draw();
        }
//        for(stUint i = 0, S = m_children.size(); i < S; i++){
//            m_children.at(1)->draw(cam, 2);
//        }
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
        if(grphx!= nullptr) material->draw(grphx->getUniforms(), *m_transform, *cam);
        if(mesh != nullptr) mesh->draw();
        for(auto child : m_children){
            dynamic_cast<STActor*>(child)->draw(material);
        }
    }
}


