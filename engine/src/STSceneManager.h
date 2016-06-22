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

class Node{
public:
    Node(){;}
protected:
    virtual void split() = 0;
    Node* next = nullptr;
};

template <class GameObject>
class QuadNode{
public:
    QuadNode(GameObject* object){}
private:
    Vector2<stReal> bounds[4];
    GameObject* entity = nullptr;
    QuadNode* children[4] = {nullptr, nullptr, nullptr, nullptr};
};

template<class GameObject>
class OctNode{
public:
    OctNode(GameObject* object){  }
private:
    Vector3<stReal> bounds[8];
    GameObject* entity = nullptr;
    OctNode* children[8] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
};

#endif //WAHOO_STSCENEMANAGER_H
