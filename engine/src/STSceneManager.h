#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include "Entity/STEntity.h"

class STActor;
class STLight;
class STInterWidget;



class STScene{
public:
    STScene(){;}

    void addActor(STActor* actor){
        actors.push_back(actor);
    }

    void addLight(STLight* light){
        lights.push_back(light);
    }

    void addUIElement(STInterWidget* ui){
        uiElements.push_back(ui);
    }

    const std::vector<STActor*> &getActors()const{ return actors; }
    const std::vector<STLight*> &getLights()const{ return lights; }
    const std::vector<STInterWidget*> &getUIElements()const{ return uiElements; }

private:
    std::vector<STActor*> actors;
    std::vector<STLight*> lights;
    std::vector<STInterWidget*> uiElements;
};

class STSceneManager{
public:
    static STSceneManager* m_instance;

    static STSceneManager* Get(){
        if(m_instance == nullptr) m_instance = new STSceneManager;
        return m_instance;
    }

    STSceneManager(){ m_NumLights = 0; }

    void addEntity(STEntity* entity){
        m_Entities.push_back(entity);
    }

    void addLight(STLight* light){

    }

    void addSkyBox(const std::string& file, const std::string& shader){
        m_skyboxName = file;
        m_skyboxShader = shader;
    }

    void addSkyCube(const std::string& file){
        m_skyboxName = file;
    }

    void addSkyboxShader(const std::string& shader){
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
};

#endif //WAHOO_STSCENEMANAGER_H
