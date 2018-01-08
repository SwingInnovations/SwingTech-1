#include "STActor.h"
#include "Components/STAABBComponent.h"
#include "Components/STEventComponent.h"
#include "Util/Loaders/STMeshLoader.h"
#include "Components/ST3DAnimationComponent.h"
#include "Components/ST3DPhysicsComponent.h"

/**
 * Creates a new Actor Entity based off defined STMeshStructure, uniqueTag, and Material.
 * @param structure
 * @param tag
 * @param material
 * @return
 */
STActor::STActor(STMesh_Structure structure, std::string &tag, STMaterial* material) {
//    m_tag = tag;
//    m_type = Actor;
//    m_visible = true;
//    addComponent(typeid(STMeshComponent), new STMeshComponent(structure));
//    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(material));
//    addComponent(typeid(STEventComponent), new STEventComponent);
//    addComponent(typeid(STAABBComponent), new STAABBComponent);
//    m_transform = std::make_shared<Transform>();
//    m_transform->setEntity(shared_from_this());
}

[[deprecated]]
STActor::STActor(STMesh_Structure meshStructure, std::map<std::string, STMaterial *> materials) {
//    m_tag = meshStructure.name;
//    m_type = Actor;
//    m_visible = true;
//    addComponent(typeid(STMeshComponent), new STMeshComponent(meshStructure));
//    if(meshStructure.materialKey.empty()) addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(new GLShader("standard"))));
//    else addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(materials.at(meshStructure.materialKey)));
//    addComponent(typeid(STEventComponent), new STEventComponent());
//    addComponent(typeid(STAABBComponent), new STAABBComponent);
}

std::shared_ptr<STActor> STActor::Create(const std::string &filename) {
    auto ret = std::make_shared<STActor>(filename);
    ret->init();
    return ret;
}

/**
 * @brief Creates Actor based off location of asset in Path.
 * @param filePath Directory to load file
 */
STActor::STActor(const std::string &filePath) {
    m_type = Actor;
    stInt flag = 0;
    bool errFlag = true;
    std::vector<STMesh_Structure> meshes;
    std::map<std::string, STMaterial*> materials;

    if(STMesh::Validate(filePath, &errFlag, &meshes, &materials)){
        for (const auto &mesh : meshes) {
            addChild_Actor(new STActor(this, mesh, materials));
        }
        return;
    }

    if(!errFlag || meshes.empty()){
            addComponent(typeid(STMeshComponent), std::make_shared<STMeshComponent>(MeshLoader::Load("base/ErrorMesh.obj")));
            addComponent(typeid(STGraphicsComponent), std::make_shared<STGraphicsComponent>(new STMaterial(new GLShader("base/errorObject"))));
            get<STEventComponent>()->addEvent("update", [](STEntity* self, STEntity* other){
                auto grphx = self->get<STGraphicsComponent>();
                grphx->setShdrUniform("intensity", (stReal)sinf(STGame::Get()->getTick() * 0.1f));
                self->transform()->setRotationMode(Transform::RotationMode::Local);
                self->transform()->setRotateY(self->transform()->getRotate().getY() + STGame::Get()->getDelta() * 0.25f);
            });
            return;
    }
    addComponent(typeid(STEventComponent), std::make_shared<STEventComponent>());
    addComponent(typeid(STMeshComponent), std::make_shared<STMeshComponent>(meshes.at(0)));
    if(meshes.at(0).m_hasAnimations){
        addComponent(typeid(ST3DAnimationComponent), std::make_shared<ST3DAnimationComponent>(meshes.at(0)));
    }
    if(meshes[0].materialKey.empty()) addComponent(typeid(STGraphicsComponent), std::make_shared<STGraphicsComponent>(new STMaterial(new GLShader("standard"))));
    else addComponent(typeid(STGraphicsComponent), std::make_shared<STGraphicsComponent>(materials.at(meshes.at(0).materialKey)));
    //addComponent(typeid(STAABBComponent), std::make_shared<STAABBComponent>(this, meshes.at(0).m_minPt, meshes.at(0).m_maxPt));
}

STActor::STActor(STEntity *parent, STMesh_Structure meshStructure, std::map<std::string, STMaterial *> materials) {
//    m_tag = meshStructure.name;
//    m_type = Actor;
//    m_visible = true;
//    addComponent(typeid(STMeshComponent), new STMeshComponent(meshStructure));
//    if(meshStructure.materialKey.empty()) addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(new GLShader("standard"))));
//    else addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(materials.at(meshStructure.materialKey)));
//    addComponent(typeid(STEventComponent), new STEventComponent());
//    if(meshStructure.m_hasAnimations){
//        addComponent(typeid(ST3DAnimationComponent), new ST3DAnimationComponent(meshStructure));
//    }
//    addComponent(typeid(STAABBComponent), new STAABBComponent);
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

/**
 *
 * @param overrideMaterial
 * @param flag
 */
void STActor::draw(STMaterial* overrideMaterial, bool flag){
    auto mesh = get<STMeshComponent>();
    auto grphx = get<STGraphicsComponent>();
    auto cam = STGame::Get()->getCamera();
    if(!m_children.empty()){
        for(auto child : m_children){
            ((STActor*)child)->draw(overrideMaterial, flag);
        }
        return;
    }
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

STActor::~STActor() {

}







