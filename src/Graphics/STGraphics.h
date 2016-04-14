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

    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize ){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, int value){  }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector2<stReal> vector){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2, stReal v3){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector3<stReal> vector){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2, stReal v3, stReal v4){ ; }
    virtual void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal> vector){;}

    Camera* camera(){
        return m_Cam;
    }


protected:
    unsigned int WIDTH, HEIGHT;
    Camera* m_Cam;
    static bool m_YUp;


};


#endif //WAHOO_STECHGRAPHICS_H
