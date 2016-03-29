#ifndef WAHOO_STECHWINDOW_H
#define WAHOO_STECHWINDOW_H

#include "../ext/GL/glew.h"
extern "C"{
    #include "../ext/SDL2/SDL.h"
    #include "../ext/SDL2/SDL_opengl.h"
};

#define GLEW_STATIC

#include <string>
#include <iostream>
#include <vector>

#include "Input.h"
#include "SGameState.h"
#include "Math/Vector.h"
#include "STResourceManager.h"

class Input;
class SGameState;
class STGraphics;
class GLGraphics;
class Camera;

class STGame {
public:
    static int RES_WIDTH;
    static int RES_HEIGHT;

    STGame();
    STGame(const std::string title, unsigned int WIDTH, unsigned int HEIGHT);
    void setOpenGLVersion(int majorVersion, int minorVersion);
    virtual ~STGame();

    void start();
    void centerCursor();
    void addState(SGameState*); // TODO - Add Structure Level Handler

    /*--General Getters and Setters--*/
    /*-The Setters-*/
    void useScript(bool v){ this->useLua = v; }
    void useFullScreen(bool v){ this->isFullScreen = v; }
    void setPause(bool v){ this->isPause = v; }
    void setTargetFPS(float val){ this->fps = (Uint32)val; }
    void showCursor(bool v){ this->isCursorOnDisplay = v; }
    void setIcon(const std::string& filePath);
    void enterState(unsigned int);

    void setClearColor(stReal, stReal, stReal, stReal);
    void setClearColor(const Vector4<stReal> clearColor);
    void addCamera(Camera* cam);

    void setWidth(int val){
        this->WIDTH = val;
        STGame::SetResolutionWidth(val);
    }

    void setHeight(int val){
        this->HEIGHT = val;
        STGame::SetResolutionHeight(val);
    }

    static void SetResolutionWidth(int val){ STGame::RES_WIDTH = val; }
    static void SetResolutionHeight(int val){ STGame::RES_HEIGHT = val; }

    /*-The Getters-*/
    Input* getInput();
    Camera* getCamera();
    STGraphics* getGraphics();
    STResourceManager* getResourceManager();
    int getWidth(){ return this->WIDTH; }
    int getHeight(){ return this->HEIGHT; }
    SDL_Window* getWindow(){ return this->m_Window; }
    Uint32 getDelta(){ return this->delta; }
protected:
    bool isRunning;
    void init(); // initialize all of the gamestates if added.
    void updateLogic();
    void updateInput(SDL_Event& event);
    void render();
    void calcDelta();
private:
    bool isPause;
    bool useLua;
    bool isFullScreen;
    bool isCursorOnDisplay;

    unsigned int m_currentIndex;
    std::vector<SGameState*> m_gameStates;
    Input* m_input;
    SDL_Window* m_Window;
    SDL_GLContext m_Context;
    SDL_Event m_e;
    STGraphics * g;
    unsigned int WIDTH, HEIGHT;
    int m_CurrentState;
    Uint32 delta, oldTime, newTime, fps;
    Vector4<stReal> m_clearColor;
    STResourceManager* resourceManager;
};


#endif //WAHOO_STECHWINDOW_H
