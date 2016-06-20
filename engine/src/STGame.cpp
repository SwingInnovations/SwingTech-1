#include "STGame.h"

#include "Graphics/STGraphics.h"
#include "Graphics/GL/GLGraphics.h"
#include "Graphics/Camera.h"

int STGame::RES_WIDTH = 0;
int STGame::RES_HEIGHT = 0;

STGame::STGame() {
    m_Window = nullptr;
    m_Context = 0;
    WIDTH = 800;
    HEIGHT = 600;
    isRunning = false;
    m_currentIndex = 0;
    isPause = false;
}

STGame::~STGame() {
    m_currentIndex = 0;
    if(!m_gameStates.empty()){
        m_gameStates.clear();
    }
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    m_Context = 0;
}

STGame::STGame(const std::string title, unsigned int WIDTH, unsigned int HEIGHT) {
    setWidth(WIDTH);
    setHeight(HEIGHT);
    if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) == -1){
        std::cout << "Error 399: Failed to load SDL in general: " << SDL_GetError() << std::endl;
        if(SDL_NumJoysticks() < 1){
            std::cout << "Error 399b: No Joysticks Detected. " << std:: endl;
        }
    }else{
        m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, this->WIDTH,
                                    this->HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        if(m_Window == nullptr){
            std::cout << "Error 400: Failed to load Window:  " << SDL_GetError() << std::endl;
        }else{
            m_input = new Input(this, m_e);
        }
    }

    STGame::SetResolutionWidth(WIDTH);
    STGame::SetResolutionHeight(HEIGHT);

    resourceManager = new STResourceManager();

    m_currentIndex = 0;
    oldTime = 0;
    newTime = SDL_GetTicks();
    delta = 0;

    isPause = false;
}

void STGame::setOpenGLVersion(int MajorVersion, int MinorVersion) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MinorVersion);
    if(MajorVersion < 3 && MinorVersion < 2){
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }else{
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }


    m_Context = SDL_GL_CreateContext(m_Window);
   // g = new LGraphics(this);
    STGraphics::RENDERER = STGraphics::OPENGL;
    if(m_Context == NULL){
        //TODO Error Code for if init fails
        std::cout << "Error 401: Unable to initialize GLContext" << std::endl;
    }else{
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();

        g = new GLGraphics(this);

        if(err != GLEW_OK){
            std::cout << "Error loading GLEW: " << glewGetErrorString(err);
        }else{
            std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
        }

        std::cout << "Using OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Using Graphics Driver: " << glGetString(GL_VENDOR) << std::endl;
    }
}

void STGame::setClearColor(stReal _x, stReal _y, stReal _z, stReal _w) {
    m_clearColor.setX(_x);
    m_clearColor.setY(_y);
    m_clearColor.setZ(_z);
    m_clearColor.setW(_w);
}

void STGame::setClearColor(const Vector4<stReal> clearColor) {
    m_clearColor = clearColor;
}

void STGame::addState(STGameState * gameState) {
    m_gameStates.push_back(gameState);
}

Input*STGame::getInput() {
    return m_input;
}

void STGame::calcDelta() {
    if(newTime > oldTime){
        delta = newTime - oldTime;
        Uint32 targetInterval = (Uint32)(1000 / this->fps);
        if(delta < targetInterval || delta > targetInterval){
            delta = targetInterval;
        }
        oldTime = newTime;
        newTime = SDL_GetTicks();
    }
}

void STGame::start(){
    isRunning = true;
    init();
    while(isRunning){
        if(!isPause){
            calcDelta();
            m_input->setDelta(delta);
        }else{
            delta = 0;
        }
        while(SDL_PollEvent(&m_e)){
            updateInput(m_e);
        }
        updateLogic();

        render();
    }
}

void STGame::init() {
    if(!m_gameStates.empty()){
        for(unsigned int i = 0; i < m_gameStates.size(); i++){
            m_gameStates.at(i)->init(this);
        }
    }
}

void STGame::updateLogic() {
    if(!m_gameStates.empty()){
        m_gameStates.at(m_currentIndex)->handleLogic(this, delta);
    }
    if(getCamera() != nullptr){
        getCamera()->update(getInput());
    }
}

void STGame::enterState(unsigned int index) {
    if(!m_gameStates.empty() && index < m_gameStates.size()){
        m_currentIndex = index;
    }
}

void STGame::updateInput(SDL_Event& event) {
    m_input->poll(event);

    if(m_input->isCloseRequested()){
        isRunning = false;
    }
    if(!m_gameStates.empty()){ m_gameStates.at(m_currentIndex)->handleInput(this, delta); }

}

void STGame::render() {
    if(!m_gameStates.empty()){
        m_gameStates.at(m_currentIndex)->render(this);
    }

    SDL_GL_SwapWindow(m_Window);
}

void STGame::addCamera(Camera* cam){
    g->setCamera(cam);
}

Camera*STGame::getCamera(){
    return g->camera();
}

STResourceManager* STGame::getResourceManager() {
    return resourceManager;
}

STGraphics* STGame::getGraphics() {
    return g;
}

void STGame::centerCursor() {
    m_input->centerMouseInWindow();
}