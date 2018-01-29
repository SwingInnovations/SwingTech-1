#include "STShadowComponent.h"

void STShadowComponent::dispose() {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        for(stUint i = 0; i < 6; i++){
            GLTexture::DisposeTex(getProperties()->shadowMapID[i]);
        }
        for(int i = 0; i < 6; i++){
            glDeleteFramebuffers(1, &getProperties()->shadowFrameBuffer[i]);
        }
    }
}

void STShadowComponent::save(std::ofstream &out) {
    m_Properties.save(out);
}

void STShadowComponent::load(std::ifstream &in) {
    m_Properties.load(in);
}

STShadowComponent::STShadowComponent() {
    m_Properties = STShadowProperties();
}

STShadowComponent::STShadowComponent(const STShadowComponent &copy) {

}