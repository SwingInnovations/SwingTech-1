#include "STechWindow.h"

STechWindow::STechWindow() {
    m_Window = nullptr;
    m_Context = 0;
    WIDTH = 800;
    HEIGHT = 600;
    isRunning = false;
    m_currentIndex = 0;
    isPause = false;
}

STechWindow::~STechWindow() {
    m_currentIndex = 0;
    if(!m_gameStates.empty()){
        m_gameStates.clear();
    }
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    m_Context = 0;
}

STechWindow::STechWindow(const std::string title, unsigned int WIDTH, unsigned int HEIGHT) {
    this->WIDTH = WIDTH;
    this->HEIGHT = HEIGHT;
    if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) == -1){
        std::cout << "Error 399: Failed to load SDL in general: " << SDL_GetError() << std::endl;
        if(SDL_NumJoysticks() < 1){
            std::cout << "Error 399b: No Joysticks Detected. " << std:: endl;
        }
    }else{
        m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, this->WIDTH,
                                    this->HEIGHT, SDL_WINDOW_OPENGL);
        if(m_Window == nullptr){
            std::cout << "Error 400: Failed to load Window:  " << SDL_GetError() << std::endl;
        }else{
            //TODO init Input and Graphics Module
            m_input = new Input(this, m_e);
            g = new STechGraphics(this);
        }
    }
    m_currentIndex = 0;
    oldTime = 0;
    newTime = SDL_GetTicks();
    delta = 0;

    isPause = false;
}

void STechWindow::setOpenGLVersion(int MajorVersion, int MinorVersion) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MinorVersion);
    if(MajorVersion < 3 && MinorVersion < 2){
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }else{
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }


    m_Context = SDL_GL_CreateContext(m_Window);
    if(m_Context == NULL){
        //TODO Error Code for if init fails
        std::cout << "Error 401: Unable to initialize GLContext" << std::endl;
    }else{
        glewExperimental = GL_TRUE;
        glewInit();

        std::cout << "Using OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Using Graphics Driver: " << glGetString(GL_VENDOR) << std::endl;
    }
}

void STechWindow::setClearColor(stReal _x, stReal _y, stReal _z, stReal _w) {
    m_clearColor.setX(_x);
    m_clearColor.setY(_y);
    m_clearColor.setZ(_z);
    m_clearColor.setW(_w);
}

void STechWindow::setClearColor(const Vector4<stReal> clearColor) {
    m_clearColor = clearColor;
}

void STechWindow::addState(SGameState* gameState) {
    m_gameStates.push_back(gameState);
}

Input* STechWindow::getInput() {
    return m_input;
}

void STechWindow::calcDelta() {
    if(newTime > oldTime){
        delta = newTime - oldTime;
        Uint32 targetInterval = (Uint32)(1.0/this->fps * 1000);
        if(delta < targetInterval || delta > targetInterval){
            delta = targetInterval;
        }
        oldTime = newTime;
        newTime = SDL_GetTicks();
    }
}

void STechWindow::start(){
    isRunning = true;
    init();
    while(isRunning){
        if(!isPause){
            calcDelta();
        }else{
            delta = 0;
        }
        while(SDL_PollEvent(&m_e)){
            updateInput(m_e);
            updateLogic();
        }
        render();
    }
}

void STechWindow::init() {
    if(!m_gameStates.empty()){
        for(unsigned int i = 0; i < m_gameStates.size(); i++){
            m_gameStates.at(i)->init(this);
        }
    }
}

void STechWindow::updateLogic() {
    if(!m_gameStates.empty()){ m_gameStates.at(m_currentIndex)->handleLogic(this, delta); }
}

void STechWindow::enterState(unsigned int index) {
    if(!m_gameStates.empty() && index < m_gameStates.size()){
        m_currentIndex = index;
    }
}

void STechWindow::updateInput(SDL_Event& event) {
    m_input->poll(event);

    if(m_input->isCloseRequested()){
        isRunning = false;
    }
    if(!m_gameStates.empty()){ m_gameStates.at(m_currentIndex)->handleInput(this, delta); }

}

void STechWindow::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(m_clearColor.getX(), m_clearColor.getY(), m_clearColor.getZ(), m_clearColor.getW());

    if(!m_gameStates.empty()){
        m_gameStates.at(m_currentIndex)->render(this);
    }

    SDL_GL_SwapWindow(m_Window);
}