#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include <map>
#include "Entity/STEntity.h"
#include "Entity/STActor.h"
#include "Entity/STLight.h"

class STLight;
class STInterWidget;

template<typename G>
class Node{
protected:
    Node* parent;
    G* data;
    virtual void split() = 0;
};

template<typename GameObject>
class QuadNode : public Node<GameObject>{
public:
    QuadNode(){
        this->parent = nullptr;
        this->data = nullptr;
        childCount = 0;
    }

    QuadNode(GameObject* data){
        this->parent = nullptr;
        this->data = data;
        childCount = 0;
    }

    QuadNode(QuadNode* parent, GameObject* data){
        this->parent = parent;
        this->data = data;
        childCount = 0;
    }

    inline void setData(GameObject* data){
        this->data = data;
    }

    inline void addChild(GameObject* childData){
        if(childCount < 4){
            if(this->data != nullptr){
                children[childCount] = new QuadNode(this, this->data);
                delete this->data;
                childCount++;
            }
            children[childCount] = new QuadNode(this, childData);
            childCount++;
        }
        //Do something when all children are filled;
    }

    GameObject* getData(){ return this->data; }

protected:
    inline void split() override {
        //Do something to split.
    }
private:
    QuadNode* children[4] = {nullptr, nullptr, nullptr, nullptr};
    stUint childCount;
};

template<typename GameObject>
class OctoNode : public Node<GameObject> {
public:
    OctoNode(){
        this->parent = nullptr;
        this->data = nullptr;
        this->childCount = 0;
    }

    OctoNode(GameObject* data){
        this->parent = nullptr;
        this->data = data;
        this->childCount = 0;
    }

    OctoNode(OctoNode* parent, GameObject* data){
        this->parent = parent;
        this->data = data;
        this->childCount = 0;
    }

    inline void setParent(OctoNode* parent){ this->parent = parent; }
    inline void setData(GameObject* data){ this->data = data; }

    inline void addChild(GameObject* data){
        if(this->childCount < 8){
            if(this->data != nullptr){
                children[this->childCount] = new OctoNode(this, this->data);
                delete this->data;
                this->data = nullptr;
                this->childCount++;
            }
            children[this->childCount] = new OctoNode(this, data);
            this->childCount++;
        }

    }
protected:
    inline void split() override {
        // Do something to split

    }

private:
    OctoNode* children[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    stUint childCount;
};

class STScene{
public:
    STScene(){
        m_index = 0;
        m_numShadows = 0;
    }

    STScene(stUint index){
        m_index = index;
    }

    inline void addActor(STActor* actor){
        actors.push_back(actor);
    }

    inline void addLight(STLight* light){
        if(light->type == STLight::DIRECTIONAL_LIGHT || light->type == STLight::SPOT_LIGHT) m_numShadows++;
        else m_numShadows += 6;
        lights.push_back(light);
    }

    inline void addUIElement(STInterWidget* ui){
        uiElements.push_back(ui);
    }

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
