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

    const std::vector<STEntity *> &getEntities() const {
        return m_Entities;
    }

    const std::vector<STLight *> &getLights() const {
        return m_Lights;
    }

private:
    std::vector<STEntity*> m_Entities;
    std::vector<STLight*> m_Lights;

    int m_NumLights;
};

#endif //WAHOO_STSCENEMANAGER_H
