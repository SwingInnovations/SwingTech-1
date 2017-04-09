#ifndef WAHOO_STECHGRAPHICS_H
#define WAHOO_STECHGRAPHICS_H

#include "../STGlobal.h"


class Camera;
class STGame;
class STSceneManager;
class STScene;

enum ST_YUpState{
    YPos_Down = false,
    YPos_Up = true
};

struct STRenderScene{
    virtual void initSkybox(const std::string& shdr, const std::string& skybox) = 0;
    virtual void drawSkybox(Camera& cam) = 0;
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
    enum RenderMode{ FORWARD, DEFERRED };
    enum Renderer{ OPENGL, VULKAN };
    static int RENDERER;
    static bool YUp;
    static Vector4<stReal> ClearColor;
    static Vector3<stReal> GlobalAmbient;
    STGraphics();
    STGraphics(STGame *);
    ~STGraphics();

    void setCamera(Camera* cam){
        m_Cam = cam;
    }

    void addCamera(Camera* cam){
        m_cameras.push_back(cam);
    }

    /**
     * Sets whether Y-Up should be up or down relative to the window.
     * @param val
     */
    static void SetYUp(bool val){ YUp = val; }
    static bool getYUpSetting(){ return YUp; }

    virtual void initScene(stUint index){;}
    virtual void drawScene(STScene* scene) = 0;
    virtual void setShader(int,Shader*){;}

    virtual void setShadowResolution(const stUint res){  }

    /*
     *
     * @return Returns the Graphics Card Driver
     */
    virtual std::string getVendor(){ return NULL; }

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

    virtual Matrix4f getOrthographicProjection()const{ return Matrix4f(); }

    Camera* getActiveCamera(){
        if(m_activeCameraIndex < m_cameras.size()) return m_cameras[m_activeCameraIndex];
        return nullptr;
    }

    Camera* camera(){
        return m_Cam;
    }

    void enablePostEffect(int index){
        m_enabledEffects|=index;
    }

    void disablePostEffect(int index){
        m_enabledEffects&=~index;
    }


protected:
    unsigned int m_enabledEffects = 0x00000000;
    unsigned int WIDTH, HEIGHT;
    Camera* m_Cam;
    std::vector<Camera*> m_cameras;
    stUint m_activeCameraIndex;
    Vector4<stReal> m_fontColor;
};


#endif //WAHOO_STECHGRAPHICS_H
