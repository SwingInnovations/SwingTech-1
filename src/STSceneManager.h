#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include "STEntity.h"

class STSceneManager{
public:
    STSceneManager(){ m_NumLights = 0; }
private:
    std::vector<STEntity*> m_Entities;

    int m_NumLights;
};

#endif //WAHOO_STSCENEMANAGER_H
