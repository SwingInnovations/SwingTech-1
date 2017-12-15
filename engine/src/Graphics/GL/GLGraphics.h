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

    inline void drawSkybox(Camera& cam){
        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);
        m_skyboxShdr->bind();
        m_skyboxShdr->update(cam);
        glActiveTexture(GL_TEXTURE0);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox);

        skyboxMesh->draw();
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }

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

    std::string getVendor();

    void cleanup();
    void init(stUint w, stUint h);

    void loadFont(const std::string&);

    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize );
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal>* color);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, std::string& msg);

    Matrix4f getOrthographicProjection()const {
        return orthoProjection;
    }

    void setScreenShader(const std::string& screenShdr) override ;

    virtual void drawScene(STScene* scene);
    void initScene(STScene* scene);

    void setResolution(stUint w, stUint h);

    /**
     * Sets the shadow resolution
     * Note - Must be 2^n
     * @param res
     */
    void setShadowResolution(const stUint res){ m_shadowRes = res;}

    void enableShadow(bool value){ m_shadows = value; }

    inline void enableBlend(){
        glEnable(GL_BLEND);
    }

    inline void disableBlend(){
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
