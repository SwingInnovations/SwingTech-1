#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include "STEntity.h"
#include "STLight.h"

class STSceneManager{
public:
    STSceneManager(){ m_NumLights = 0; }

    void addEntity(STEntity* entity){
        m_Entities.push_back(entity);
    }

    void addLight(STLight* light){

    }

    void addSkyBox(const std::string& file, const std::string& shader){
        skybox_Name = file;
        skybox_shader = shader;
    }

    void addSkyCube(const std::string& file){
        skybox_Name = file;
    }

    void addSkyboxShader(const std::string& shader){
        skybox_shader = shader;
    }

    const std::vector<STEntity *> &getEntities() const {
        return m_Entities;
    }

    const std::vector<STLight *> &getLights() const {
        return m_Lights;
    }

    const std::string getSkyboxName()const{ return skybox_Name; }
    const std::string getSkyboxShader()const{return skybox_shader;}
private:
    std::vector<STEntity*> m_Entities;
    std::vector<STLight*> m_Lights;

    std::string skybox_Name;
    std::string skybox_shader;

    int m_NumLights;
};

#endif //WAHOO_STSCENEMANAGER_H
