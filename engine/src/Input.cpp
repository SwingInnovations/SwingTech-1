#include <fstream>
#include "Input.h"

static const int NUM_KEYS = 512;
static const int NUM_MOUSE = 0x40;

static bool keyPressed[NUM_KEYS];
static bool lastKey[NUM_KEYS];
static bool mouseButtonPressed[NUM_MOUSE];
int lastChar = 0;

Input* Input::m_instance = nullptr;

Input::Input() {
    closeRequested = false;
    cursorBound = true;

    mouseX = 0;
    mouseY = 0;
    mouseSensitivity = 0.035f;

    for(int i = 0; i < NUM_KEYS; i++){
        keyPressed[i] = false;
        lastKey[i] = false;
    }

    for(int i = 0; i < NUM_MOUSE; i++){
        mouseButtonPressed[i] = false;
    }
}

void InputMap::initKeyMap() {
    m_keyMap["KEY_A"] = KEY::KEY_A;
    m_keyMap["KEY_B"] = KEY::KEY_B;
    m_keyMap["KEY_C"] = KEY::KEY_C;
    m_keyMap["KEY_D"] = KEY::KEY_D;
    m_keyMap["KEY_E"] = KEY::KEY_E;
    m_keyMap["KEY_F"] = KEY::KEY_F;
    m_keyMap["KEY_G"] = KEY::KEY_G;
    m_keyMap["KEY_H"] = KEY::KEY_H;
    m_keyMap["KEY_I"] = KEY::KEY_I;
    m_keyMap["KEY_J"] = KEY::KEY_J;
    m_keyMap["KEY_K"] = KEY::KEY_K;
    m_keyMap["KEY_L"] = KEY::KEY_L;
    m_keyMap["KEY_M"] = KEY::KEY_M;
    m_keyMap["KEY_N"] = KEY::KEY_N;
    m_keyMap["KEY_O"] = KEY::KEY_O;
    m_keyMap["KEY_P"] = KEY::KEY_P;
    m_keyMap["KEY_Q"] = KEY::KEY_Q;
    m_keyMap["KEY_R"] = KEY::KEY_R;
    m_keyMap["KEY_S"] = KEY::KEY_S;
    m_keyMap["KEY_T"] = KEY::KEY_T;
    m_keyMap["KEY_U"] = KEY::KEY_U;
    m_keyMap["KEY_V"] = KEY::KEY_V;
    m_keyMap["KEY_W"] = KEY::KEY_W;
    m_keyMap["KEY_X"] = KEY::KEY_X;
    m_keyMap["KEY_Y"] = KEY::KEY_Y;
    m_keyMap["KEY_Z"] = KEY::KEY_Z;

    m_keyMap["KEY_1"] = KEY::KEY_1;
    m_keyMap["KEY_2"] = KEY::KEY_2;
    m_keyMap["KEY_3"] = KEY::KEY_3;
    m_keyMap["KEY_4"] = KEY::KEY_4;
    m_keyMap["KEY_5"] = KEY::KEY_5;
    m_keyMap["KEY_6"] = KEY::KEY_6;
    m_keyMap["KEY_7"] = KEY::KEY_7;
    m_keyMap["KEY_8"] = KEY::KEY_8;
    m_keyMap["KEY_9"] = KEY::KEY_9;
    m_keyMap["KEY_0"] = KEY::KEY_0;

    m_keyMap["KEY_ENTER"] = KEY::KEY_ENTER;
    m_keyMap["KEY_RETURN"] = KEY::KEY_ENTER;
    m_keyMap["KEY_ESC"] = KEY::KEY_ESC;
    m_keyMap["KEY_BACKSPACE"] = KEY::KEY_BACKSPACE;
    m_keyMap["KEY_TAB"] = KEY::KEY_TAB;
    m_keyMap["KEY_SPACE"] = KEY::KEY_SPACE;

    m_keyMap["KEY_L_CONTROL"] = KEY::KEY_L_CONTROL;
    m_keyMap["KEY_L_SHIFT"] = KEY::KEY_L_SHIFT;
    m_keyMap["KEY_L_ALT"] = KEY::KEY_L_ALT;

    m_keyMap["KEY_R_CONTROL"] = KEY::KEY_R_CONTROL;
    m_keyMap["KEY_R_SHIFT"] = KEY::KEY_R_SHIFT;
    m_keyMap["KEY_R_ALT"] = KEY::KEY_R_ALT;

    m_movementMap["FORWARD"] = MOVEMENT::FORWARD;
    m_movementMap["BACKWARD"] = MOVEMENT::BACKWARD;
    m_movementMap["STRAFE_LEFT"] = MOVEMENT::STRAFE_LEFT;
    m_movementMap["STRAFE_RIGHT"] = MOVEMENT::STRAFE_RIGHT;
    m_movementMap["JUMP"] = MOVEMENT::JUMP;
    m_movementMap["AIM"] = MOVEMENT::AIM;
    m_movementMap["SNEAK"] = MOVEMENT::SNEAK;
    m_movementMap["CROUCH"] = MOVEMENT::CROUCH;
    m_movementMap["LEFT"] = MOVEMENT::LEFT;
    m_movementMap["RIGHT"] = MOVEMENT::RIGHT;
    m_movementMap["UP"] = MOVEMENT::UP;
    m_movementMap["DOWN"] = MOVEMENT::DOWN;
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
        if(lastKey[lastChar]) lastKey[lastChar] = false;
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
    return false;
}

bool Input::isKeyPressed(int key) {
    if(keyPressed[key] && !lastKey[key]){
        keyPressed[key] = false;
        lastKey[key] = true;
        lastChar = key;
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


InputMap::InputMap() = default;

InputMap::InputMap(const std::string &filePath) {
    initKeyMap();
    json  j;
    std::ifstream in(filePath);
    in >> j;
    in.close();

    for(json::iterator it = j.begin(); it != j.end(); ++it){
        if(it.key() == "KEY"){
            json jt = *it;
            for(json::iterator it2 = jt.begin(); it2 != jt.end(); ++it2)
                addMapping(m_movementMap[it2.key()], m_keyMap[it2.value()]);
        }
    }

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
