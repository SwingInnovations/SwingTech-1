#ifndef WAHOO_GLGRAPHICS_H
#define WAHOO_GLGRAPHICS_H

#include <regex>

#if __MINGW32__
#include "../../../include/GL/glew.h"
#else
#include <GL/glew.h>
#endif


#include "../../Entity/STLight.h"
#include "../../Entity/STEntity.h"
#include "../../Application/STSceneManager.h"
#include "../STGraphics.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMesh.h"


class GLGraphics;

struct Character{
    GLuint texID;
    Vector2<int> size;
    Vector2<int> bearing;
    GLuint Advance;
};

struct GLRenderScene : public STRenderScene{
    GLRenderScene(){
        m_skybox = 0;
        m_skyboxShdr = nullptr;
        m_initiated = false;
        skyboxMesh = new GLMesh(new STCube(1000));
    }

    inline void initSkybox(const std::string& shdr, const std::string& map){
        m_skybox = GLTexture::loadCubemapTexture(map);
        m_skyboxShdr = new GLShader(shdr);
    }

    inline void drawSkybox(STCamera* camera) override ;

    void dispose(){
        delete m_skyboxShdr;
        glDeleteTextures(1, &m_skybox);
        delete skyboxMesh;
    }

    GLuint m_skybox;
    GLShader* m_skyboxShdr;
    GLMesh* skyboxMesh;
};

class GLGraphics : public STGraphics{
public:
    GLGraphics();
    GLGraphics(STGame*);

    std::string getVendor() override;

    void cleanup() override ;
    void init(stUint w, stUint h) override ;

    void loadFont(const std::string&)override;

    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize ) override;
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal>* color) override;
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value) override;
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, std::string& msg) override;

    Matrix4f getOrthographicProjection()const override;

    void setScreenShader(const std::string& screenShdr) override ;

    void drawScene(STScene* scene) override;
    void initScene(STScene* scene) override;

    void setResolution(stUint w, stUint h);

    /**
     * Sets the shadow resolution
     * Note - Must be 2^n
     * @param res
     */
    void setShadowResolution(stUint res)override;

    void enableShadow(bool value)override;

    inline void enableBlend()override{
        glEnable(GL_BLEND);
    }

    inline void disableBlend()override {
        glDisable(GL_BLEND);
    }

    static Vector3<stReal> TextColor;

   ~GLGraphics(){
       delete screenShdr;
       delete Bloom_Composite;
       delete Bloom_Threshold;
       delete Motion_Blur;
       delete Tone_Mapping;
       delete FXAAShader;

       delete m_directionalLightMat;
       delete m_pointLightMat;
       delete m_spotLightMat;
       delete m_albedoMat;
       delete m_IBLMat;
       delete m_velocityMat;
    }

protected:

private:
    std::map<GLchar, Character> characters;
    GLuint textVAO;
    GLuint textVBO;
    GLShader* textShader;

    GLuint shadowArray;
    GLuint rboDepth;

    Matrix4f orthoProjection;
    GLuint frameBuffer;
    GLuint frameTexBuffer;
    GLuint velocityBuffer;
    GLuint velocityTexture;
    GLuint rendBuffer;
    GLuint  bloomThresTex;
    GLuint bloomThresBuf;

    //Render Buffer
    GLuint gTransparencyBuffer;
    GLuint gBuffer;
    GLuint gPosition;
    GLuint gNormal;
    GLuint gTangent;
    GLuint gColorSpec;
    GLuint gMRA;        //Store Metallic; Roughness; Ambient Occlusion.


    GLShader* screenShdr;
    GLShader* Bloom_Composite;
    GLShader* Bloom_Threshold;
    GLShader* Motion_Blur;
    GLShader* Tone_Mapping;
    GLShader* FXAAShader;
    GLShader* GBufferShader;
    GLShader* Deff_LightPassShdr;

    GLMesh* screenQuad;
    STMaterial* m_GBufferOverrideMat;
    STMaterial* m_GBufferOverrideSkinnedMat;
    STMaterial* m_directionalLightMat;
    STMaterial* m_directionalSkinnedOverrideMat;
    STMaterial* m_directShadowMat;
    STMaterial* m_pointLightMat;
    STMaterial* m_spotLightMat;
    STMaterial* m_albedoMat;
    STMaterial* m_IBLMat;
    STMaterial* m_velocityMat;

    bool m_shadows;

    void Bloom();
    void MotionBlur();
    void ToneMapping();
    void RenderScreenWithShader(const std::string& shaderName);
    void RenderScreenWithShader(GLShader* shader);

    stUint m_shadowRes;
};



#endif //WAHOO_GLGRAPHICS_H
