#ifndef WAHOO_STECHGRAPHICS_H
#define WAHOO_STECHGRAPHICS_H

#include "../Math/STCore.h"
#include "../Math/Vector.h"
#include "../Math/Matrix.h"
#include "Shader.h"

#include <string>
#include <SDL2/SDL_video.h>

class Camera;
class STGame;
class STSceneManager;
class STScene;

struct STRenderInfo{
    enum STRenderer : unsigned char{
        OPENGL = 0,
        VULKAN = 1
    };

    stUint minVersion = 0;
    stUint maxVersion = 1;
    STRenderer renderer = OPENGL;
};

enum ST_YUpState : unsigned char{
    YPos_Down = false,
    YPos_Up = true
};

struct STRenderScene{
    virtual void initSkybox(const std::string& shdr, const std::string& skybox){;}
    virtual void drawSkybox(Camera& cam){;};
    virtual void drawSkybox(STCamera* cam) = 0;
    virtual void dispose() = 0;
    bool m_initiated = false;
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

    enum Deferred_RenderNetwork : unsigned char{
        BLINNPHONG = 0,
        PBR = 1,
        CUSTOM = 2
    };

    enum RenderMode{ FORWARD, DEFERRED };
    enum Renderer{ OPENGL, VULKAN };
    static int RENDERER;
    static bool YUp;
    static Vector4D ClearColor;
    static Vector3D GlobalAmbient;
    STGraphics();
    explicit STGraphics(STGame *);
    ~STGraphics();

    virtual void cleanup() = 0;
    virtual void init(stUint w, stUint h) = 0;
	virtual void init(STGame* game) = 0;

    virtual void setScreenShader(const std::string&) = 0;

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

    /*
     *
     * @return Returns the Graphics Card Driver
     */
    virtual std::string getVendor(){ return nullptr; }

    void setFontColor(const Vector4<stReal>& vec){ m_fontColor = vec; }

    Vector4<stReal> getFontColor()const { return m_fontColor; }

	void enableShadow(bool);
	void setShadowResolution(stUint w);

    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize ){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal>* color){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, std::string& msg){ ; }


    virtual void enableBlend() = 0;
    virtual void disableBlend() = 0;
    virtual void loadFont(const std::string&) = 0;  //TODO Implement this.

    virtual Matrix4f getOrthographicProjection()const{ return Matrix4f(); }

    STCamera* getCamera();

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

    virtual void swapBuffer(SDL_Window* window) = 0;

protected:
    unsigned int m_enabledEffects = 0x00000000;
    unsigned int WIDTH, HEIGHT;
    Vector4D m_fontColor;
    RenderMode m_renderMode;
	stUint m_shadowResolution;
	bool m_useShadow;
};


#endif //WAHOO_STECHGRAPHICS_H
