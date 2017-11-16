#ifndef WAHOO_STECHGRAPHICS_H
#define WAHOO_STECHGRAPHICS_H

#include "../Math/STCore.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "Shader.h"

#include <string>

class Camera;
class STGame;
class STSceneManager;
class STScene;

enum ST_YUpState{
    YPos_Down = false,
    YPos_Up = true
};

struct STRenderScene{
    virtual void initSkybox(const std::string& shdr, const std::string& skybox){;}
    virtual void drawSkybox(Camera& cam){;};
    bool m_initiated;
};

class STGraphics {
public:
    enum POST_EFFECT: unsigned int
    {
        BLOOM = 1,
        MOTION_BLUR = 2,
        TONE_MAPPING=4,
        FXAA=8
    };

    enum Deferred_RenderNetwork : char{
        BLINNPHONG = 0,
        PBR = 1,
        CUSTOM = 2
    };

    enum RenderMode{ FORWARD, DEFERRED };
    enum Renderer{ OPENGL, VULKAN };
    static int RENDERER;
    static bool YUp;
    static Vector4<stReal> ClearColor;
    static Vector3<stReal> GlobalAmbient;
    STGraphics();
    STGraphics(STGame *);
    ~STGraphics();

    virtual void cleanup() = 0;
    virtual void init(stUint w, stUint h) = 0;

    void setCurrentCamera(stUint cameraIndex);

    void addCamera(Camera* cam){
        m_cameras.push_back(cam);
    }

    void setResolution(stUint w, stUint h){;}

    /**
     * Sets whether Y-Up should be up or down relative to the window.
     * @param val
     */
    static void SetYUp(bool val){ YUp = val; }
    static bool getYUpSetting(){ return YUp; }
    virtual void initScene(STScene* scene) = 0;
    virtual void drawScene(STScene* scene) = 0;
    virtual void setShader(int,Shader*){;}

    virtual void setShadowResolution(const stUint res){  }

    /*
     *
     * @return Returns the Graphics Card Driver
     */
    virtual std::string getVendor(){ return nullptr; }

    void setFontColor(const Vector4<stReal>& vec){ m_fontColor = vec; }

    Vector4<stReal> getFontColor()const { return m_fontColor; }

    void setCameraIndex(stUint index){ this->m_activeCameraIndex = index; }
    stUint getActiveCameraIndex()const{ return this->m_activeCameraIndex; }

    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize ){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal>* color){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, std::string& msg){ ; }

    virtual void enableShadow(bool) = 0;
    virtual void enableBlend() = 0;
    virtual void disableBlend() = 0;
    virtual void loadFont(const std::string&) = 0;  //TODO Implement this.

    virtual Matrix4f getOrthographicProjection()const{ return Matrix4f(); }

    Camera* getActiveCamera(){
        if(m_activeCameraIndex < m_cameras.size()) return m_cameras[m_activeCameraIndex];
        return nullptr;
    }


    void enablePostEffect(int index){
        m_enabledEffects|=index;
    }

    void disablePostEffect(int index){
        m_enabledEffects&=~index;
    }

    void setRenderMode(RenderMode rm){
        m_renderMode = rm;
    }

    RenderMode getRenderMode()const {
        return m_renderMode;
    }


protected:
    unsigned int m_enabledEffects = 0x00000000;
    unsigned int WIDTH, HEIGHT;
    std::vector<Camera*> m_cameras;
    stUint m_activeCameraIndex;
    Vector4<stReal> m_fontColor;
    RenderMode m_renderMode;
};


#endif //WAHOO_STECHGRAPHICS_H
