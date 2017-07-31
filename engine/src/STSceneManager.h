#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include <map>
#include "Entity/STEntity.h"
#include "Entity/STActor.h"
#include "Entity/STLight.h"
#include "Math/Shape/BoundingBox.h"
#include "Util/Data_Structure/STQueue.h"

class STLight;
class STInterWidget;

class OctNode{
public:
    explicit OctNode(STBoundingBox* boundingBox){
        this->boundingBox = boundingBox;
        this->data = NULL;
        for (auto &i : children) i = NULL;
    }

    explicit OctNode(const OctNode& copy){
        this->boundingBox = copy.boundingBox;
        this->data = copy.data;
    }

    OctNode(Vector3<stReal>& originPt, Vector3<stReal>& extants){
        this->boundingBox = new STBoundingBox;
        this->boundingBox->setDimensions(originPt, extants);
        this->data = NULL;
        for (auto &i : children) i = NULL;
    }

    OctNode(STEntity* data, STBoundingBox* boundingBox){
        this->boundingBox = boundingBox;
        this->data = data;
    }

    ~OctNode(){
        delete this->boundingBox;
        delete this->data;
        for(stUint i = 0; i < 8; i++){
            delete children[i];
        }
    }

    void insert(STEntity* newEntity){
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

    int getOctantContainingPt(const Vector3<stReal>& point){
        int oct = 0;
        Vector3<stReal> originPoint = boundingBox->getOriginPoint();
        if(point.getX() >= originPoint.getX()) oct |= 4;
        if(point.getY() >= originPoint.getY()) oct |= 2;
        if(point.getZ() >= originPoint.getZ()) oct |= 1;
        return oct;
    }

    bool isLeafNode()const{
        for(short i = 0; i < 8; ++i){
            if(children[i] != NULL) return false;
        }
        return true;
    }

    void update(){
        if(data != NULL){
            data->update();
            if(!boundingBox->contains(data->transform()->getTranslate())){
                //Flag for re-insertion;
            }
        }
        for (auto &i : children) {
            if(i != NULL) i->update();
        }
    }

private:
    STEntity* data;
    STBoundingBox* boundingBox;
    OctNode* parent;
    OctNode* children[8];
};

class STScene{
public:
    STScene(){
        m_index = 0;
        m_numShadows = 0;
        skyboxShader = "skybox";
        rootNode = new OctNode(new STBoundingBox(Vector3<stReal>(-1000.f, -1000.f, -1000.f), Vector3<stReal>(1000.f, 1000.f, 1000.f)));
    }

    STScene(stUint index){
        m_index = index;
        rootNode = new OctNode(new STBoundingBox(Vector3<stReal>(-1000.f, -1000.f, -1000.f), Vector3<stReal>(1000.f, 1000.f, 1000.f)));
    }

    inline void addActor(STActor* actor){
        actors.push_back(actor);
        pendingEntities.push(actor);
    }

    inline void addLight(STLight* light){
        if(light->get<STLightComponent>()->getType() == STLightComponent::DIRECTIONAL_LIGHT ||
                light->get<STLightComponent>()->getType() == STLightComponent::SPOT_LIGHT) m_numShadows++;
        else m_numShadows += 6;
        lights.push_back(light);
    }

    inline void addUIElement(STInterWidget* ui){
        uiElements.push_back(ui);
    }

    inline void update(){
        while(pendingEntities.size() > 0){
            rootNode->insert(pendingEntities.pop());
        }
        rootNode->update();
    }

    /**
     * Sets the skybox using the default skybox shader.
     * @param filePath
     */
    inline void addSkybox(const std::string& filePath){
        this->skyboxShader = "skybox";
        this->skyboxName = filePath;
    }

    /**
     * Sets the skybox using an override shader.
     * @param file
     * @param shader
     */
    inline void addSkybox(const std::string& file, const std::string& shader){
        this->skyboxName = file;
        this->skyboxShader = shader;
    }

    const std::vector<STActor*> &getActors()const{ return actors; }
    const std::vector<STLight*> &getLights()const{ return lights; }
    const std::vector<STInterWidget*> &getUIElements()const{ return uiElements; }

    const std::string& getSkyboxName()const{ return skyboxName; }
    const std::string& getSkyboxShader()const{ return skyboxShader; }

    const stUint getIndex()const{ return m_index; }
    const stUint getShadowCount()const{ return m_numShadows; }

private:
    stUint m_index;
    stUint m_numShadows;
    STQueue<STEntity*> pendingEntities;
    OctNode* rootNode;
    std::vector<STActor*> actors;
    std::vector<STLight*> lights;
    std::vector<STInterWidget*> uiElements;
    std::string skyboxName;
    std::string skyboxShader;
};

class STSceneManager{
public:
    static STSceneManager* m_Instance;

    static STSceneManager* Get(){
        if(m_Instance == nullptr) m_Instance = new STSceneManager;
        return m_Instance;
    }

    STSceneManager(){ m_NumLights = 0; }

    inline STScene* initScene(const stUint index){
        scenes.insert(std::pair<stUint, STScene*>(index, new STScene(index)));
        //Allocate something to manage the scene
        auto grphx = STGame::Get()->getGraphics();
        grphx->initScene(index);
        return scenes[index];
    }

    inline STScene* getScene(stUint index){
        if(index < scenes.size()){
            return scenes[index];
        }
    }

    inline void addEntity(STEntity* entity){
        m_Entities.push_back(entity);
    }

    inline void addLight(STLight* light){

    }

    inline void addSkyBox(const std::string& file, const std::string& shader){
        m_skyboxName = file;
        m_skyboxShader = shader;
    }

    inline void addSkyCube(const std::string& file){
        m_skyboxName = file;
    }

    inline void addSkyboxShader(const std::string& shader){
        m_skyboxShader = shader;
    }

    const std::vector<STEntity *> &getEntities() const {
        return m_Entities;
    }

    const std::vector<STLight *> &getLights() const {
        return m_Lights;
    }

    const std::string getSkyboxName()const{ return m_skyboxName; }
    const std::string getSkyboxShader()const{return m_skyboxShader;}
private:
    std::vector<STEntity*> m_Entities;
    std::vector<STLight*> m_Lights;

    std::string m_skyboxName;
    std::string m_skyboxShader;

    int m_NumLights;

    std::map<stUint, STScene*> scenes;
};

#endif //WAHOO_STSCENEMANAGER_H
