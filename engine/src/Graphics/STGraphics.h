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
    enum RenderMode{ FORWARD, DEFERRED };
    enum Renderer{ OPENGL, VULKAN };
    static int RENDERER;
    static bool YUp;
    static Vector4<stReal> ClearColor;

    STGraphics();
    STGraphics(STGame *);
    ~STGraphics();

    void setCamera(Camera* cam){
        m_Cam = cam;
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

    /*!
     *
     * @return Returns the Graphics Card Driver
     */
    virtual std::string getVendor(){ return NULL; }

    void setFontColor(const Vector4<stReal>& vec){ m_fontColor = vec; }

    Vector4<stReal> getFontColor()const { return m_fontColor; }

    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize ){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal>* color){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, std::string& msg){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, int value){  }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector2<stReal> vector){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2, stReal v3){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector3<stReal> vector){ ; }

    Camera* camera(){
        return m_Cam;
    }


protected:
    unsigned int WIDTH, HEIGHT;
    Camera* m_Cam;
    Vector4<stReal> m_fontColor;

};


#endif //WAHOO_STECHGRAPHICS_H
