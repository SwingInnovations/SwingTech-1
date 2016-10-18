#include "Input.h"

static const int NUM_KEYS = 512;
static const int NUM_MOUSE = 0x40;

static bool keyPressed[NUM_KEYS];
static bool mouseButtonPressed[NUM_MOUSE];

Input* Input::m_instance = nullptr;

Input::Input() {
    closeRequested = false;
    cursorBound = true;

    mouseX = 0;
    mouseY = 0;
    mouseSensitivity = 0.035f;

    for(int i = 0; i < NUM_KEYS; i++){
        keyPressed[i] = false;
    }

    for(int i = 0; i < NUM_MOUSE; i++){
        mouseButtonPressed[i] = false;
    }
}

Input::Input(STGame * window, SDL_Event& event) {
    this->e = event;
    parent = window;
    closeRequested = false;
    cursorBound = false;
    mouseX = 0;
    mouseY = 0;
    screenWidth = window->getWidth();
    screenHeight = window->getHeight();
    templateWin = window->getWindow();
    delta = window->getDelta();

    moveSpeed = 0.025f;
    mouseSensitivity = 0.035f;

    for(unsigned int i = 0, l = NUM_KEYS; i < l; i++){
        keyPressed[i] = false;
    }

    for(unsigned int i = 0, l = NUM_MOUSE; i < l; i++){
        mouseButtonPressed[i] = false;
    }
}

Input::~Input() {
    delete inputMap;
}

void Input::poll(SDL_Event& event) {
    if(event.type == SDL_QUIT){
        closeRequested = true;
    }

    if(event.type == SDL_KEYDOWN){
        keyPressed[event.key.keysym.scancode] = true;
    }

    if(event.type == SDL_KEYUP){
        keyPressed[event.key.keysym.scancode] = false;
    }

    if(event.type == SDL_MOUSEMOTION){
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }

    if(event.type == SDL_MOUSEBUTTONDOWN){
        mouseButtonPressed[event.button.button] = true;
    }

    if(event.type == SDL_MOUSEBUTTONUP){
        mouseButtonPressed[event.button.button] = false;
    }
}

void Input::setCursorVisible(bool val) {
    if(val){
        SDL_ShowCursor(SDL_ENABLE);
    }else{
        SDL_ShowCursor(SDL_DISABLE);
    }
}

void Input::centerMouseInWindow() {
    int cX = screenWidth/2;
    int cY = screenHeight/2;
    SDL_WarpMouseInWindow(templateWin, cX, cY);
}

void Input::addJoystick(int id) {
    if(SDL_NumJoysticks() < 1 || id < SDL_NumJoysticks()){
        std::cout << "Error, invalid amount of Joysticks! " << std::endl;
    }else{
        joysticks[id] = SDL_JoystickOpen(id);
    }
}

void Input::addJoystick() {
    int joystickCount = (int)joyStick.size()-1;
    if(joystickCount < 0){
        joystickCount = 0;
    }
    SDL_Joystick* temp = SDL_JoystickOpen(joystickCount);
    joyStick.push_back(temp);
}

bool Input::isKeyDown(int key){
    if(key > -1)    return keyPressed[key];
    else return false;
}

bool Input::isKeyPressed(int key) {
    if(keyPressed[key]){
        keyPressed[key] = false;
        return true;
    }
    return false;
}

bool Input::isMouseDown(int button) {
    return mouseButtonPressed[button];
}

bool Input::isMousePressed(int button) {
    if(mouseButtonPressed[button]){
        mouseButtonPressed[button] = false;
        return true;
    }
    return false;
}

Input *Input::Get() {
    return Input::m_instance;
}

Input *Input::Start(STGame *app, SDL_Event &e) {
    m_instance = new Input(app, e);
    return m_instance;
}

const char Input::getInputCharacter() const {
    return m_currentCharacter;
}


InputMap::InputMap() {

}

InputMap::InputMap(const std::string &filePath) {
    // TODO implement file reader to pull keymapping

}

void InputMap::addMapping(int target, int key) {
    InputKey a;
    a.setTarget(target);
    a.setKey(key);
    mapping.push_back(a);
}

int InputMap::get(int target){
    // Return the map for the given enum
    if(mapping.size() > 0){
        for(auto ent : mapping){
            if(ent.getTarget() == target){
                return ent.getKey();
            }
        }
    }
    return -1;
}
