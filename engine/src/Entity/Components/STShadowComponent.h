#ifndef SWINGTECH1_STSHADOWCOMPONENT_H
#define SWINGTECH1_STSHADOWCOMPONENT_H

#include <map>

#include "STComponent.h"

#include "../../Math/STMath.h"
#include "../../Graphics/STGraphics.h"
#include "../../Graphics/GL/GLTexture.h"

struct STShadowProperties{
    stUint shadowIndex{};
    stUint shadowMapID[6]{};
    stUint shadowFrameBuffer[6]{};
    Matrix4f projections[6];

    STShadowProperties() = default;

    void save(std::ofstream& out){
        out.write((char*)&shadowIndex, sizeof(shadowIndex));
        out.write((char*)&shadowMapID, sizeof(shadowMapID));
        out.write((char*)&shadowFrameBuffer, sizeof(shadowFrameBuffer));
        for (auto &projection : projections) {
            projection.save(out);
        }
    }

    void load(std::ifstream& in){
        in.read((char*)&shadowIndex, sizeof(shadowIndex));
        in.read((char*)&shadowMapID, sizeof(shadowMapID));
        in.read((char*)&shadowFrameBuffer, sizeof(shadowFrameBuffer));
        for (auto &projection : projections) {
            projection.load(in);
        }
    }
};

class STShadowComponent : public STComponent{
public:
    STShadowComponent();
    STShadowComponent(const STShadowComponent& copy);
    /**
     * Gets the Shadow Properties
     * @return Shadow Properties Struct
     */
    STShadowProperties* getProperties(){ return &m_Properties; }
    void update()override{

    }

    void draw()override{

    }

    void save(std::ofstream& out) override;

    void load(std::ifstream& in) override;

    void dispose() override;
private:
   STShadowProperties m_Properties;
};



#endif //SWINGTECH1_STSHADOWCOMPONENT_H
