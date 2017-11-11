#ifndef SWINGTECH1_STSHADOWCOMPONENT_H
#define SWINGTECH1_STSHADOWCOMPONENT_H

#include "STComponent.h"

struct STShadowProperties{
    stUint shadowIndex;
    stUint shadowMapID[6];
    stUint shadowFrameBuffer[6];
    Matrix4f projections[6];
};

class STShadowComponent : public STComponent{
public:
    STShadowComponent(){;}
    STShadowProperties* getProperties(){ return &m_Properties; }
    void update(){

    }

    void draw(){

    }
private:
   STShadowProperties m_Properties;
};

#endif //SWINGTECH1_STSHADOWCOMPONENT_H
