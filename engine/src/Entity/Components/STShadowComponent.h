#ifndef SWINGTECH1_STSHADOWCOMPONENT_H
#define SWINGTECH1_STSHADOWCOMPONENT_H

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>

#include "STComponent.h"

struct STShadowProperties{
    stUint shadowIndex;
    stUint shadowMapID[6];
    stUint shadowFrameBuffer[6];
    Matrix4f projections[6];
    template<class Archive> void serialize(Archive& ar){
        ar(shadowIndex, shadowMapID, shadowFrameBuffer);
    }
};

class STShadowComponent : public STComponent{
public:
    STShadowComponent(){;}
    /**
     * Gets the Shadow Properties
     * @return Shadow Properties Struct
     */
    STShadowProperties* getProperties(){ return &m_Properties; }
    void update(){

    }

    void draw(){

    }

    template<class Archive> void serialize(Archive& ar);
    void dispose(){
        if(STGraphics::RENDERER == STGraphics::OPENGL){
            for(stUint i = 0; i < 6; i++){
                GLTexture::DisposeTex(getProperties()->shadowMapID[i]);
            }
            for(int i = 0; i < 6; i++){
                glDeleteFramebuffers(1, &getProperties()->shadowFrameBuffer[i]);
            }
        }
    }
private:
   STShadowProperties m_Properties;
};

template<class Archive>
void STShadowComponent::serialize(Archive &ar) {
    ar(m_Properties);
}

#endif //SWINGTECH1_STSHADOWCOMPONENT_H
