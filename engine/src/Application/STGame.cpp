#include <SDL2/SDL_video.h>
#include "STGame.h"

#include "../Graphics/STGraphics.h"
#include "../Graphics/GL/GLGraphics.h"
#include "../Physics/Bullet/BulletPhysics.h"

#include "../Entity/Components/STLightComponent.h"
#include "../Entity/Components/STEventComponent.h"
#include "../Entity/Components/ST3DAnimationComponent.h"
#include "../Entity/Components/ST3DPhysicsComponent.h"
#include "../Graphics/VK/VKGraphics.h"

int STGame::RES_WIDTH = 0;
int STGame::RES_HEIGHT = 0;
STGame* STGame::m_instance = nullptr;

class STShadowComponent;

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
   for (auto &m_gameState : m_gameStates) {
       delete m_gameState;
   }
    m_gameStates.clear();
    g->cleanup();
    delete g;
    delete m_physics;
    SDL_GL_DeleteContext(m_Context);
    SDL_DestroyWindow(m_Window);
    m_Window = nullptr;
    m_Context = 0;
}

STGame::STGame(const std::string &title, stUint width, stUint height, STRenderInfo &renderMode) {
    setWidth(width);
    setHeight(height);
    auto registerBaseComponents = STComponentObjectFactory::Get();
    registerBaseComponents->registerClass("STMeshComponent", [=]() -> STComponent*{ return new STMeshComponent; });
    registerBaseComponents->registerClass("STRendererComponent", [=]() -> STComponent*{ return new STRendererComponent; });
    registerBaseComponents->registerClass("ST3DAnimationComponent", [=]() -> STComponent*{ return new ST3DAnimationComponent; });
    registerBaseComponents->registerClass("ST3DPhysicsComponent", [=]() -> STComponent*{ return new ST3DPhysicsComponent; });
    registerBaseComponents->registerClass("STLightComponent", [=]() -> STComponent*{ return new STLightComponent; });
    registerBaseComponents->registerClass("STShadowComponent", [=]() -> STComponent*{ return new STShadowComponent; });
    registerBaseComponents->registerClass("STEventComponent", [=]() -> STComponent*{ return new STEventComponent; });
    registerBaseComponents->registerClass("STScriptComponent", [=]() -> STComponent*{ return new STScriptComponent; });
    registerBaseComponents->registerClass("STCameraComponent", [=]() -> STComponent*{ return new STCameraComponent; });
    if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) == -1){
        std::cout << "Error: Failed to load SDL in general" << SDL_GetError() << std::endl;
    }else{
        SDL_version linked;
        SDL_GetVersion(&linked);
        printf("Linked using SDL Version: %d.%d.%d\n", linked.major, linked
        .minor, linked.patch);
        if(renderMode.renderer == STRenderInfo::OPENGL){
            //Initialize OpenGL
            m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
            if(m_Window == nullptr){
                std::cout << "Error: Failed to initialize SDL Window" << SDL_GetError() << std::endl;
            }else{
                Input::Start(this, m_e);
            }
        }else{
            m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
            if(m_Window == nullptr){

            }else{
                Input::Start(this, m_e);
            }
        }
    }
    m_currentIndex = 0;
    oldTime = 0;
    newTime = SDL_GetTicks();
    delta = 0;

    isPause = false;
}

STGame::STGame(const std::string title, unsigned int WIDTH, unsigned int HEIGHT) {
    setWidth(WIDTH);
    setHeight(HEIGHT);
    auto registerBaseComponents = STComponentObjectFactory::Get();
    registerBaseComponents->registerClass("STMeshComponent", [=]() -> STComponent*{ return new STMeshComponent; });
    registerBaseComponents->registerClass("STRendererComponent", [=]() -> STComponent*{ return new STRendererComponent; });
    registerBaseComponents->registerClass("ST3DAnimationComponent", [=]() -> STComponent*{ return new ST3DAnimationComponent; });
    registerBaseComponents->registerClass("ST3DPhysicsComponent", [=]() -> STComponent*{ return new ST3DPhysicsComponent; });
    registerBaseComponents->registerClass("STLightComponent", [=]() -> STComponent*{ return new STLightComponent; });
    registerBaseComponents->registerClass("STShadowComponent", [=]() -> STComponent*{ return new STShadowComponent; });
    registerBaseComponents->registerClass("STEventComponent", [=]() -> STComponent*{ return new STEventComponent; });
    registerBaseComponents->registerClass("STScriptComponent", [=]() -> STComponent*{ return new STScriptComponent; });
    if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) == -1){
        std::cout << "Error 399: Failed to load SDL in general: " << SDL_GetError() << std::endl;
        if(SDL_NumJoysticks() < 1){
            std::cout << "Error 399b: No Joysticks Detected. " << std:: endl;
        }
    }else{
        m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, this->WIDTH,
                                    this->HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if(m_Window == nullptr){
            std::cout << "Error 400: Failed to load Window:  " << SDL_GetError() << std::endl;
        }else{
            Input::Start(this, m_e);
        }
    }

    STGame::SetResolutionWidth(WIDTH);
    STGame::SetResolutionHeight(HEIGHT);

    m_currentIndex = 0;
    oldTime = 0;
    newTime = SDL_GetTicks();
    delta = 0;

    isPause = false;
}

void STGame::setOpenGLVersion(int MajorVersion, int MinorVersion) {
    m_graphics_MAJOR = MajorVersion;
    m_graphics_MINOR = MinorVersion;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MinorVersion);
    if(MajorVersion < 3 && MinorVersion < 2){
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
        m_graphics_Profile = 0;
    }else{
        m_graphics_Profile = 1;
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    }


    m_Context = SDL_GL_CreateContext(m_Window);
    STGraphics::RENDERER = STGraphics::OPENGL;
    if(m_Context == NULL){
        std::cout << "Error 401: Unable to initialize GLContext" << std::endl;
    }else{
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();

        if(err != GLEW_OK){
            std::cout << "Error loading GLEW: " << glewGetErrorString(err);
        }else{
            std::cout << "Using GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;
        }

        std::cout << "Using OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Using Graphics Driver: " << glGetString(GL_VENDOR) << std::endl;
        g = new GLGraphics(this);
    }
}

void STGame::initializeVulkan() {
    //SDL_Vulkan_CreateSurface(m_Window, m_vkInstance, &m_vkSurface);
    g = new VKGraphics(this);
}

void STGame::addState(STGameState * gameState) {
    m_gameStates.push_back(gameState);
}

Input* STGame::getInput() {
    return Input::Get();
}

void STGame::calcDelta() {
    if(newTime > oldTime){
        delta = newTime - oldTime;
        Uint32 targetInterval = (Uint32)(1000.0f / this->fps);
        if(delta < targetInterval || delta > targetInterval){
            delta = targetInterval;
        }
        oldTime = newTime;
        newTime = SDL_GetTicks();
    }
}

stReal STGame::getDeltaTIme() const {
    return (stReal)(oldTime - newTime) / 1000.f;
}

void STGame::start(){
    isRunning = true;
    init();
    if(m_physics) m_physics->initScene(m_gameStates[m_currentIndex]->getScene());
    while(isRunning){
        if(!isPause){
            calcDelta();
            Input::Get()->setDelta(delta);
            if(m_physics){
                m_physics->update(delta);
            }
        }else{
            delta = 0;
        }
        while(SDL_PollEvent(&m_e)) Input::Get()->poll(m_e);
        update();

        render();
    }
    if(Input::m_instance != nullptr) delete Input::m_instance;
    if(STGame::m_instance != nullptr) delete STGame::m_instance;
}

void STGame::init() {

    if(!m_gameStates.empty()){
        m_gameStates[m_currentIndex]->init_Internal(this);
        m_gameStates[m_currentIndex]->init(this);
    }
}

void STGame::enterState(unsigned int index) {
    if(!m_gameStates.empty() && index < m_gameStates.size()){
        auto physicsValid = (m_physics != nullptr);
        if(physicsValid){ m_physics->dispose(); }
        m_currentIndex = index;
        if(physicsValid && m_gameStates[m_currentIndex]->getScene() != nullptr){ m_physics->initScene(m_gameStates[m_currentIndex]->getScene()); }
    }
}

void STGame::update() {
    auto input = Input::Get();
    if(input->isCloseRequested()){
        isRunning = false;
    }
    if(!m_gameStates.empty() && m_currentIndex < m_gameStates.size()) m_gameStates[m_currentIndex]->update(this);
}

void STGame::render() {
    if(!m_gameStates.empty()){
        m_gameStates.at(m_currentIndex)->render(this);
    }

    g->swapBuffer(m_Window);
}

STGraphics* STGame::getGraphics() {
    return g;
}

void STGame::centerCursor() {
    Input::Get()->centerMouseInWindow();
}

STGame *STGame::Init(const std::string &title, const stUint WIDTH, const stUint HEIGHT) {
    m_instance = new STGame(title, WIDTH, HEIGHT);
    return m_instance;
}

STGame *STGame::Init(const std::string &title, stUint width, stUint height, STPhysics::PhysicsEngine mode) {
    m_instance = new STGame(title, width, height);
    m_instance->InitPhysics(mode);
    return m_instance;
}

STGame *STGame::Init(const std::string &title, stUint width, stUint height, STRenderInfo &renderInfo,
                     STPhysics::PhysicsEngine mode) {
    m_instance = new STGame(title, width, height, renderInfo);
    m_instance->InitPhysics(mode);
    if(renderInfo.renderer == STRenderInfo::OPENGL){
        m_instance->setOpenGLVersion(renderInfo.maxVersion, renderInfo.minVersion);
    }else{
        m_instance->initializeVulkan();
    }
    return m_instance;
}

STGame *STGame::Get() {
    return m_instance;
}

void STGame::setIcon(const std::string &filePath) {
    SDL_Surface* img = nullptr;
    img = IMG_Load(filePath.c_str());
    if(img == nullptr){
        std::cerr << "Failed to load filepath. Invalid file?" << std::endl;
    }
    SDL_SetWindowIcon(m_Window, img);

    SDL_FreeSurface(img);
    img = 0;
}

void STGame::setFullScreen(int flag) {
    SDL_DisplayMode DM;

    switch(flag){
        case 0:
            SDL_SetWindowFullscreen(m_Window, 0);
            g->setResolution(WIDTH, HEIGHT);
            break;
        case 1:
            SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
            SDL_GetDesktopDisplayMode(0, &DM);
            g->setResolution(DM.w, DM.h);
            std::cout << "Fullscreen Desktop with " << DM.w << " : " << DM.h << std::endl;
            break;
        default:
            ;
    }
}

STScene *STGame::getCurrentScene() {
    return m_gameStates[m_currentIndex]->getScene();
}

void STGame::InitPhysics(STPhysics::PhysicsEngine mode) {
    if(mode == STPhysics::BULLET){
        m_physics = new BulletPhysics;
        m_physics->init(mode);
        m_physicsMode = mode;
    }
}

stInt STGame::getPhysicsMode() const {
    return m_physicsMode;
}

STPhysics *STGame::getPhysics() {
    return m_physics;
}

stUint STGame::getTargetFPS() const {
    return fps;
}





