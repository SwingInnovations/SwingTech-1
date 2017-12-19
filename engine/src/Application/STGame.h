#ifndef WAHOO_STECHWINDOW_H
#define WAHOO_STECHWINDOW_H

#if __MINGW32__
#include "../include/GL/glew.h"
extern "C"{
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_opengl.h>
};
#else
#include <GL/glew.h>
extern "C"{
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
};
#endif

#define  GLEW_STATIC

#include <iostream>
#include <vector>

#include "Input.h"
#include "../Physics/STPhysics.h"
#include "STGameState.h"
#include "../Math/Vector.h"

class Input;
class STScene;
class STGameState;
class STGraphics;
class GLGraphics;
class Camera;

//! STGame Class
/*!
 *  Central class for creating a game with Swing Tech 1. Class holds
 *  information regarding current game state, a resource manager,
 *  and delta time.
 */
class STGame {
public:
    static int RES_WIDTH;
    static int RES_HEIGHT;

    static STGame* m_instance;

    static STGame* Init(const std::string& title, const stUint WIDTH, const stUint HEIGHT);
    static STGame* Init(const std::string& title, stUint width, stUint height, STPhysics::PhysicsEngine mode);
    static STGame* Get();

    enum DIMENSION_MODE{
        DIM_2D = 0,
        DIM_3D = 1
    };

    //! Constructor
    /*!
     *  Default Constructor.
     */
    STGame();

    //! Constructor
    /*!
     *  \param title Window Title.
     *  \param WIDTH Window Width.
     *  \param HEIGHT Window Height.
     */
    STGame(const std::string title, unsigned int WIDTH, unsigned int HEIGHT);
    //! Sets the OpenGL Version
    /*!
     *  \param majorVersion Sets the major OpenGL Version.
     *  \param minorversion Sets the minor OpenGL Version.
     */
    void setOpenGLVersion(int majorVersion, int minorVersion);
    //! A destructor
    virtual ~STGame();
    //! Begins the game.
    /*!
     * Starts the game loop.
     */
    void start();
    //! Centers Cursor to screen.
    void centerCursor();
    //! Adds STGameState to game.
    /*!
     *  \param STGameState* STGameState to be added to the game.
     */
    void addState(STGameState *); // TODO - Add Structure Level Handler

    /*--General Getters and Setters--*/
    /*-The Setters-*/
    inline void useScript(bool v){ this->useLua = v; }
    //! Sets Game to Fullscreen
    /*!
     *  \param v Fullscreen state.
     */
    inline void useFullScreen(bool v){ this->isFullScreen = v; }
    //! Sets Game to Pause.
    /*!
     *  \param v Pause state.
     */
    inline void setPause(bool v){ this->isPause = v; }

    //! Sets Target FPS for game.
    /*!
     *  \param val Target FPS(Frames per Second)
     */
    void setTargetFPS(float val){ this->fps = (Uint32)val; }

    //! Sets Cursor Visible
    /*!
     *  \param v Cursor Visibility state.
     */
    void showCursor(bool v){ this->isCursorOnDisplay = v; }
    /** Sets the Window Icon
     *
     * @param filePath Path to window icon.
     */
    void setIcon(const std::string& filePath);

    //! Sets Current State of Game
    /*!
     *  \param v Current State
     */
    void enterState(unsigned int);

    //! Sets Camera for Game
    /*!
     *  Sets Camera for STGame. Note, camera will be persistant
     *  for all game states.
     *  \param cam Pointer to Camera
     */
    void addCamera(Camera* cam);

    inline void setDimension(DIMENSION_MODE dim){
        this->dimMode = dim;
    }

    void setFullScreen(int);

    static void SetResolutionWidth(int val){ STGame::RES_WIDTH = val; }
    static void SetResolutionHeight(int val){ STGame::RES_HEIGHT = val; }

    /**
     * Sets the Active Index for the Camera.
     * @param index
     */

    void setActiveCamera(stUint index);

    /*-The Getters-*/
    //! Gets pointer to Input
    /*!
     *  Note: This is global and persistant,
     *  for all STGameStates.
     *  \return Returns pointer to Input
     */
    Input* getInput();
    //! Gets pointer to Input
    /*!
     *  Note: This is global and persistant,
     *  for all STGameStates.
     *  \return Returns pointer to Camera.
     */
    Camera* getCamera();
    //! Gets pointer to STGraphics
    /*!
     *  Note: This is global and persistant,
     *  for all STGameStates.
     *  \return Returns pointer to Camera.
     */
    STGraphics* getGraphics();
    int getWidth(){ return this->WIDTH; }
    int getHeight(){ return this->HEIGHT; }

    int getTick(){ return SDL_GetTicks(); }

    /**
     * Get the current active scene in the game.
     * @return STScene Object
     */
    STScene* GetCurrentScene();

    int getGraphicsMajorVersion(){ return this->m_graphics_MAJOR; }
    int getGraphicsMinorVersion(){ return this->m_graphics_MINOR; }
    int getGraphicsProfile(){ return this->m_graphics_Profile; }

    const DIMENSION_MODE getDimensionMode()const{ return this->dimMode; }
    //! Gets Pointer to SDL_Window
    SDL_Window* getWindow(){ return this->m_Window; }/*! \return pointer to SDL_Window */
    //! Gets Delta time.
    Uint32 getDelta(){ return this->delta; } /*! \return Delta time */
    stReal getDeltaTIme() const ;
    stInt getPhysicsMode()const;
protected:
    bool isRunning;
    //! Initializes Game States
    void init(); /*! Initializes Game states when necessary, deactivates last state */
    //! Renders Scene
    void update();
    void render();
    //! Calculates Delta for every CPU cycle
    void calcDelta();

private:
    bool isPause;
    bool useLua;
    bool isFullScreen;
    bool isCursorOnDisplay;

    void setWidth(int val){
        this->WIDTH = val;
        STGame::SetResolutionWidth(val);
    }

    void setHeight(int val){
        this->HEIGHT = val;
        STGame::SetResolutionHeight(val);
    }

    void InitPhysics(STPhysics::PhysicsEngine mode);

    unsigned int m_currentIndex;
    std::vector<STGameState *> m_gameStates;
    SDL_Window* m_Window;
    SDL_GLContext m_Context;
    SDL_Event m_e;

    STGraphics * g;
    STPhysics* m_physics;
    unsigned int WIDTH, HEIGHT;
    int m_CurrentState;

    stInt m_graphics_MAJOR;
    stInt m_graphics_MINOR;
    stInt m_graphics_Profile;
    stInt m_physicsMode;

    Uint32 delta, oldTime, newTime, fps;
    DIMENSION_MODE dimMode;
};


#endif //WAHOO_STECHWINDOW_H
