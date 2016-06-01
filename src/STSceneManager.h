#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include "STEntity.h"
#include "STLight.h"

template<typename GameEntity>
class QuadNode;

template<typename GameEntity>
class OctNode;

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

template <class GameObject>
class QuadNode{
public:
    QuadNode(GameObject* object){}
private:
    Vector2<stReal> bounds[4];
    GameObject* children[4];
};

template<class GameObject>
class OctNode{
public:
    OctNode(GameObject* object){  }
private:
    Vector3<stReal> bounds[8];
    GameObject* children[8];
};

#endif //WAHOO_STSCENEMANAGER_H
