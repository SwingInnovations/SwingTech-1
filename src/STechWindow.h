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

class Input;
class SGameState;

class STechWindow {
public:
    STechWindow();
    STechWindow(const std::string title, unsigned int WIDTH, unsigned int HEIGHT);
    void setOpenGLVersion(int majorVersion, int minorVersion);
    virtual ~STechWindow();

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

    /*-The Getters-*/
    Input* getInput();
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
    unsigned int WIDTH, HEIGHT;
    int m_CurrentState;
    Uint32 delta, oldTime, newTime, fps;
    Vector4<stReal> m_clearColor;
};


#endif //WAHOO_STECHWINDOW_H
