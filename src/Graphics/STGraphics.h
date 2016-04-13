#ifndef WAHOO_STECHGRAPHICS_H
#define WAHOO_STECHGRAPHICS_H

#include "../STGlobal.h"
#include "../STSceneManager.h"

class Camera;
class STGame;

enum ST_YUpState{
    YPos_Down = false,
    YPos_Up = true
};

struct STRenderPass{
    virtual void bind(){;}
    virtual void unBind(){;}
    virtual void draw(STGraphics*){;}
};

class STGraphics {
public:
    enum RenderMode{ FORWARD, DEFERRED };
    enum Renderer{ OPENGL, VULKAN };
    static int RENDERER;
    static Vector4<stReal> ClearColor;

    STGraphics();
    STGraphics(STGame *);
    ~STGraphics();

    void setCamera(Camera* cam){
        m_Cam = cam;
    }

    static void setYUp(bool val){ m_YUp = val; }
    static bool getYUpSetting(){ return m_YUp; }

    virtual void addRenderPass(STSceneManager* scene){;}
    virtual void drawScene(STSceneManager* sceneManager){;}
    virtual void setShader(int,Shader*){;}

    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector3<stReal> color){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize ){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value){ ; }

    Camera* camera(){
        return m_Cam;
    }


protected:
    unsigned int WIDTH, HEIGHT;
    Camera* m_Cam;
    static bool m_YUp;


};


#endif //WAHOO_STECHGRAPHICS_H
