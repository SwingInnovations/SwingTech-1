#include "STSceneManager.h"
#include "../Entity/Components/STEventComponent.h"
#include "../Entity/Components/ST3DPhysicsComponent.h"

OctNode::OctNode(STBoundingBox *boundingBox) {
    this->boundingBox = boundingBox;
    this->data = NULL;
    for (auto &i : children) i = NULL;
}

OctNode::OctNode(const OctNode &copy) {
    this->boundingBox = copy.boundingBox;
    this->data = copy.data;
}

OctNode::OctNode(Vector3<stReal> &originPt, Vector3<stReal> &extants) {
    this->boundingBox = new STBoundingBox;
    this->boundingBox->setDimensions(originPt, extants);
    this->data = NULL;
    for (auto &i : children) i = NULL;
}

OctNode::OctNode(STEntity *data, STBoundingBox *boundingBox) {
    this->boundingBox = boundingBox;
    this->data = data;
}

OctNode::~OctNode() {
    delete this->boundingBox;
    delete this->data;
    for(stUint i = 0; i < 8; i++){
        delete children[i];
    }
}

void OctNode::insert(STEntity *newEntity) {
    if(isLeafNode()){
        if(this->data == NULL){
            this->data = newEntity;
        }else{
            STEntity* oldData = this->data;
            this->data = NULL;

            for(stUint i = 0; i < 8; i++){
                auto originPt = this->boundingBox->getOriginPoint();
                auto extants = this->boundingBox->getExtants();
                stReal nX = originPt.getX() + extants.getX() * (i&4 ? 0.5f : -0.5f);
                stReal nY = originPt.getY() + extants.getY() * (i&2 ? 0.5f : -0.5f);
                stReal nZ = originPt.getZ() + extants.getZ() * (i&1 ? 0.5f : -0.5f);
                Vector3<stReal> newOrigin(nX, nY, nZ);
                extants *= 0.5f;
                children[i] = new OctNode(newOrigin, extants);
                children[i]->parent = this;
            }
            auto oldPt = getOctantContainingPt(oldData->transform()->getTranslate());
            auto newPt = getOctantContainingPt(newEntity->transform()->getTranslate());
            if(oldPt == newPt){
                int c = 0;
                while(children[c]->data != NULL){
                    c++;
                }
                newPt = c % 8;
            }
            children[oldPt]->insert(oldData);
            children[newPt]->insert(newEntity);
        }
    }else{
        int octant = getOctantContainingPt(newEntity->transform()->getTranslate());
        children[octant]->insert(newEntity);
    }
}

int OctNode::getOctantContainingPt(const Vector3<stReal> &point) {
    int oct = 0;
    Vector3<stReal> originPoint = boundingBox->getOriginPoint();
    if(point.getX() >= originPoint.getX()) oct |= 4;
    if(point.getY() >= originPoint.getY()) oct |= 2;
    if(point.getZ() >= originPoint.getZ()) oct |= 1;
    return oct;
}

bool OctNode::isLeafNode() const {
    for(short i = 0; i < 8; ++i){
        if(children[i] != NULL) return false;
    }
    return true;
}

void OctNode::update() {
    if(data != NULL){
        data->update();
    }
    for (auto &i : children) {
        if(i != NULL) i->update();
    }
}

STScene::STScene() {
    m_index = 0;
    m_numShadows = 0;
    m_activeCameraIndex = 0;
    skyboxShader = "skybox";
    addCamera(STCamera::Create(STCameraProperties::STViewProfile(), Vector3D(0, 0, 0)));
    rootNode = new OctNode(new STBoundingBox(Vector3<stReal>(-1000.f, -1000.f, -1000.f), Vector3<stReal>(1000.f, 1000.f, 1000.f)));
}

void STScene::update() {
//    while(pendingEntities.size() > 0){
//        rootNode->insert(pendingEntities.pop());
//    }
//    rootNode->update(); //Updates all entities.
    getActiveCamera()->update();

    for(const auto& actor : actors){
        if(actor){
            actor->update();
        }
    }

    for(const auto& light : lights){
        light->update();
    }

    for(auto ent : removeQueue){
        STScene::RemoveEntity(ent);
    }

    if(!removeQueue.empty()) removeQueue.clear();
}

void STScene::addUIElement(STInterWidget *ui) {
    uiElements.push_back(ui);
}

STScene::STScene(stUint index) {
    m_index = index;
    m_activeCameraIndex = 0;
    addCamera(STCamera::Create(STCameraProperties::STViewProfile(), Vector3D(0, 0, 0)));
    rootNode = new OctNode(new STBoundingBox(Vector3<stReal>(-1000.f, -1000.f, -1000.f), Vector3<stReal>(1000.f, 1000.f, 1000.f)));
}

STScene::~STScene() {
    delete rootNode;
    actors.clear();
    lights.clear();
    uiElements.clear();
}

void STScene::addSkybox(const std::string &filePath) {
    this->skyboxShader = "skybox";
    this->skyboxName = filePath;
}

void STScene::addSkybox(const std::string &file, const std::string &shader) {
    this->skyboxName = file;
    this->skyboxShader = shader;
}

void STScene::setRenderScene(STRenderScene* scene) {
    m_renderScene = scene;
}

void STScene::sendMessage(const std::string &msg) {
    for(const auto& actor : actors){
        actor->get<STEventComponent>()->setEvent(msg);
    }
}

void STScene::dispose() {
    for(const auto& actor : actors){
        actor->dispose();
    }

    for(const auto& light : lights){
        light->dispose();
    }
    actors.clear();
    m_renderScene->dispose();
}

void STScene::addActor(std::shared_ptr<STActor> actor) {
    actors.emplace_back(actor);
    auto p = actor->get<ST3DPhysicsComponent>();
    if(p != nullptr){
        STGame::Get()->getPhysics()->addToPhysicsWorld(p->getRigidBody());
    }
}

void STScene::addLight(std::shared_ptr<STLight> light) {
    if(light->get<STLightComponent>()->getType() == STLightComponent::DIRECTIONAL_LIGHT ||
       light->get<STLightComponent>()->getType() == STLightComponent::SPOT_LIGHT) m_numShadows++;
    else m_numShadows += 6;
    lights.emplace_back(light);
}

void STScene::save(std::ofstream &out) {
    stUint numActors, numLights;
    numActors = (stUint)actors.size();
    numLights = (stUint)lights.size();
    out.write((char*)&numActors, sizeof(stUint));
    out.write((char*)&numLights, sizeof(stUint));
    for(auto& actor : actors){
        actor->save(out);
    }

    for(auto& light : lights){
        light->save(out);
    }
}

void STScene::load(std::ifstream &in) {
    stUint numActors, numLights;
    in.read((char*)&numActors, sizeof(stUint));
    in.read((char*)&numLights, sizeof(stUint));
    for(stUint i = 0; i < numActors; i++){
        auto actor = std::make_shared<STActor>();
        actor->load(in);
        actors.emplace_back(actor);
    }

    for(stUint i = 0; i < numLights; i++){
        auto light = std::make_shared<STLight>();
        light->load(in);
        lights.emplace_back(light);
    }
}

void STScene::RemoveEntity(STEntity *entity) {
    auto type = entity->getType();
    auto actors = STGame::Get()->getCurrentScene()->actors;
    auto lights = STGame::Get()->getCurrentScene()->lights;

    switch(entity->getType()){
        case STEntity::Type ::Actor:
            for(stUint i = 0; i < actors.size(); i++){
                if(actors[i].get() == entity){
                    actors[i]->dispose();
                    actors.erase(actors.begin() + i);
                    STGame::Get()->getCurrentScene()->actors = actors;
                }
            }
            break;
        case STEntity::Type::Light:
            for(stUint i = 0; i < lights.size(); i++){
                if(lights[i].get() == entity){
                    lights.erase(lights.begin() + i);
                }
            }
            break;
        default:
            ;
    }
}

void STScene::RemoveEntityQueue(STEntity *entity) {
    auto scene = STGame::Get()->getCurrentScene();
    scene->removeQueue.emplace_back(entity);
}

STCamera *STScene::getActiveCamera() const {
    return m_cameras[m_activeCameraIndex].get();
}

void STScene::addCamera(std::shared_ptr<STCamera> newCamera) {
    m_cameras.emplace_back(newCamera);
}
