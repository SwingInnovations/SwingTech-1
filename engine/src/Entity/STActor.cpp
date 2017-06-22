#include "STActor.h"
#include "Components/STEventComponent.h"
#include "Components/STAABBComponent.h"
#include "Util/Loaders/STOBJLoader.h"

//STActor::STActor(const std::string &filePath, const int type, STMaterial *material) {
//    m_transform = new Transform();
//    m_type = Actor;
//    m_visible = true;
//    addComponent(typeid(STMeshComponent), new STMeshComponent(filePath, type));
//    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
//    addComponent(typeid(STEventComponent), new STEventComponent());
//    m_visible = true;
//}


/**
 * Creates a new Actor Entity based off defined STMeshStructure, uniqueTag, and Material.
 * @param structure
 * @param tag
 * @param material
 * @return
 */
STActor::STActor(STMesh_Structure structure, std::string &tag, STMaterial* material) {
    m_transform = new Transform;
    m_tag = tag;
    m_type = Actor;
    m_visible = true;
    addComponent(typeid(STMeshComponent), new STMeshComponent(structure));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
    addComponent(typeid(STEventComponent), new STEventComponent);
    addComponent(typeid(STAABBComponent), new STAABBComponent((STEntity*)this, structure.m_minPt, structure.m_maxPt));
}

STActor::STActor(STMesh_Structure meshStructure, std::map<std::string, STMaterial *> materials) {
    m_transform = new Transform;
    m_tag = meshStructure.name;
    m_type = Actor;
    m_visible = true;
    addComponent(typeid(STMeshComponent), new STMeshComponent(meshStructure));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(materials.at(meshStructure.materialKey)));
    addComponent(typeid(STEventComponent), new STEventComponent);
    addComponent(typeid(STAABBComponent), new STAABBComponent((STEntity*)this, meshStructure.m_minPt, meshStructure.m_maxPt));
}

STActor::STActor(const std::string &filePath) {
    m_transform = new Transform();
    m_type = Actor;
    stInt flag = 0;
    bool errFlag = true;
    std::vector<STMesh_Structure> meshes;
    std::map<std::string, STMaterial*> materials;
    addComponent(typeid(STEventComponent), new STEventComponent);
    if(STMesh::Validate(filePath, &errFlag, &meshes, &materials)){
        for(stUint i = 0, S = meshes.size(); i < S; i++) {
            addChild_Actor(new STActor(meshes.at(i), materials));
        }
        return;
    }else{
        if(!errFlag || meshes.size() < 1){
            addComponent(typeid(STMeshComponent), new STMeshComponent(STOBJLoader::Load("base/ErrorMesh.obj")));
            addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(new GLShader("base/errorObject"))));
            get<STEventComponent>()->updateEvent([](STEntity* self){
                auto grphx = self->get<STGraphicsComponent>();
                grphx->setShdrUniform("intensity", (stReal)sin(STGame::Get()->getTick() * 0.01f));
            });
            transform()->setRotateY(180.f);
            return;
        }else{
            addComponent(typeid(STMeshComponent), new STMeshComponent(meshes.at(0)));
            addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(materials.at(meshes.at(0).materialKey)));
            addComponent(typeid(STAABBComponent), new STAABBComponent(this, meshes.at(0).m_minPt, meshes.at(0).m_maxPt));
        }
    }
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
        if(!errFlag || meshes.size() < 1){
            addComponent(typeid(STMeshComponent), new STMeshComponent(STOBJLoader::Load("base/ErrorMesh.obj")));
            addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(new GLShader("base/errorObject"))));
            get<STEventComponent>()->updateEvent([](STEntity* self){
                auto grphx = self->get<STGraphicsComponent>();
                grphx->setShdrUniform("intensity", (stReal)sin(STGame::Get()->getTick() * 0.01f));
            });
            this->transform()->setRotateY(180.0f);
            return;
        }else{
            addComponent(typeid(STMeshComponent), new STMeshComponent(meshes.at(0)));
            addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
            addComponent(typeid(STAABBComponent), new STAABBComponent((STEntity*)this, meshes[0].m_minPt, meshes[0].m_maxPt));
        }
    }

    if(tags.size() > 0)
        m_tag = tags.at(0);
    else m_tag = "Actor";

}

/**
 * Draws actor and all children if visible.
 */
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
    }
}

/**
 * Draws the scene with specified camera and draw mode override.
 * @param camera
 * @param drawMode
 */
void STActor::draw(Camera *camera, int drawMode) {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        grphx->draw(*m_transform, *camera);
        mesh->draw(drawMode);
    }
}

/**
 * Draws the scene using material as an override.
 * @param material
 */
void STActor::draw(STMaterial *material) {
    if(m_visible){
        auto mesh = this->get<STMeshComponent>();
        auto grphx = this->get<STGraphicsComponent>();
        auto cam = STGame::Get()->getCamera();
        if(grphx!= nullptr) material->draw(grphx->GetUniforms(), *m_transform, *cam);
        if(mesh != nullptr) mesh->draw();
        for(auto child : m_children){
            dynamic_cast<STActor*>(child)->draw(material);
        }
    }
}

void STActor::draw(STMaterial* overrideMaterial, bool flag){
    auto mesh = get<STMeshComponent>();
    auto grphx = get<STGraphicsComponent>();
    auto cam = STGame::Get()->getCamera();
    if(flag){
        overrideMaterial->draw(grphx->GetUniforms(), grphx->getMaterial()->GetUniforms(), *m_transform, *cam);
        mesh->draw();
        for(auto child : m_children){
            dynamic_cast<STActor*>(child)->draw(overrideMaterial, flag);
        }
    }else{
        overrideMaterial->draw(grphx->GetUniforms(), *m_transform, *cam);
        mesh->draw();
        for(auto child : m_children){
            dynamic_cast<STActor*>(child)->draw(overrideMaterial, flag);
        }
    }
}




