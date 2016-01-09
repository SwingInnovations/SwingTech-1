#ifndef WAHOO_INPUT_H
#define WAHOO_INPUT_H

#include "../ext/SDL2/SDL.h"
#include "../ext/SDL2/SDL_joystick.h"
#include "../ext/SDL2/SDL_gamecontroller.h"
#include "Math/Vector.h"

#include <string>
#include <vector>
#include <c++/sstream>

#include "STechWindow.h"

class STechWindow;

namespace MOVEMENT{
  enum{
    FORWARD = 0,
      BACKWARD = 1,
      STRAFE_LEFT = 2,
      STRAFE_RIGHT = 3,
      JUMP = 4,
      AIM = 5,
      SNEAK = 6,
      CROUCH = 7,

      LEFT = 8,
      RIGHT = 9,
      UP = 10,
      DOWN = 11
  };
};

namespace JOYSTICK_AXIS{
    enum{
        X_AXIS = 0,
        Y_AXIS = 1,
        Z_AXIS = 2
    };
};

namespace JOYSTICK_BUTTON{
  enum{
    BUTTON_1 = 0,
      BUTTON_2 = 1,
      BUTTON_3 = 2,
      BUTTON_4 = 3,
      BUTTON_5 = 4,
      BUTTON_6 = 5,
      BUTTON_7 = 6,
      BUTTON_8 = 7,
      BUTTON_9 = 8,
      BUTTON_10 = 9,
      BUTTON_11 = 10,
      BUTTON_12 = 11,
      BUTTON_13 = 12,
      BUTTON_14 = 13,
      BUTTON_15 = 14,
      BUTTON_16 = 15
  };
};

namespace KEY{
    enum{
        KEY_A = 4,
        KEY_B = 5,
        KEY_C = 6,
        KEY_D = 7,
        KEY_E = 8,
        KEY_F = 9,
        KEY_G = 10,
        KEY_H = 11,
        KEY_I = 12,
        KEY_J = 13,
        KEY_K = 14,
        KEY_L = 15,
        KEY_M = 16,
        KEY_N = 17,
        KEY_O = 18,
        KEY_P = 19,
        KEY_Q = 20,
        KEY_R = 21,
        KEY_S = 22,
        KEY_T = 23,
        KEY_U = 24,
        KEY_V = 25,
        KEY_W = 26,
        KEY_X = 27,
        KEY_Y = 28,
        KEY_Z = 29,

        KEY_1 = 30,
        KEY_2 = 31,
        KEY_3 = 32,
        KEY_4 = 33,
        KEY_5 = 34,
        KEY_6 = 35,
        KEY_7 = 36,
        KEY_8 = 37,
        KEY_9 = 38,
        KEY_0 = 39,

        KEY_ENTER = 40,
        KEY_RETURN = 40,
        KEY_ESC = 41,
        KEY_BACKSPACE = 42,
        KEY_TAB = 43,
        KEY_SPACE = 44,

        KEY_L_CONTROL = 224,
        KEY_L_SHIFT = 225,
        KEY_L_ALT = 226,
        KEY_R_CONTROL = 228,
        KEY_R_SHIFT = 229,
        KEY_R_ALT = 230
    };
};

struct InputKey{
public:
    InputKey(){
        // - Default Constructor
        this->target = 0;
        this->key = 0;
    }

    InputKey(int target, int key){
        this->target = target;
        this->key = key;
    }

    int getTarget() const {
        return target;
    }

    void setTarget(int target) {
        this->target = target;
    }

    int getKey() const {
        return key;
    }

    void setKey(int key) {
        this->key = key;
    }

private:
    int target;
    int key;
};

class InputMap{
public:
    InputMap();
    InputMap(const std::string& filePath);

    void addMapping(int target, int key);
    int get(int target){

    }// - Return the Key for the given target

    std::string info() {
        std::ostringstream ret;
        for (unsigned int i = 0, m = mapping.size(); i < m; i++) {
            ret << "Target: " << mapping.at(i).getTarget() << " Key: " << mapping.at(i).getKey();
        }
        return ret.str();
    }
private:
    std::vector<InputKey> mapping;
};

class Input {
public:
    Input();
    Input(STechWindow* app, SDL_Event& e);
    ~Input();

    void poll(SDL_Event&);
    void requestClose(){ closeRequested = true; }
    void setCursorVisible(bool);

    void centerMouseInWindow();

    void setInputMap(InputMap* map){ inputMap = map; }
    void setMoveSpeed(float speed){ moveSpeed = speed; }
    void setMouseSensitivity(float speed){ mouseSensitivity = speed; }
    void setCursorBound(bool v){ cursorBound = v; }
    InputMap* inputMapping(){ return inputMap; }

    template<typename T> Vector2<T> getMouseCoords(){
        T _x = (T)mouseX;
        T _y = (T)mouseY;
        Vector2<T> ret(_x, _y);
        return ret;
    }

    void addJoystick(int id);
    void addJoystick();

    bool isKeyDown(int);
    bool isKeyPressed(int);
    bool isMouseDown(int);
    bool isMousePressed(int);
    bool isCursorBound(){ return cursorBound; }
    bool isCloseRequested(){ return closeRequested; }

    float getMouseSensitivity()const{ return mouseSensitivity; }
    Uint32 getDelta()const{ return delta; }

    double getJoystickAxis(int joyIndex, int axis){
        return (double)SDL_JoystickGetAxis(joysticks[joyIndex], axis);
    }

    bool getJoystickButton(int joyIndex, int button){
        return SDL_JoystickGetButton(joysticks[joyIndex], button);
    }

private:
    bool closeRequested;
    bool cursorBound;

    SDL_Event e;
    SDL_Joystick* joysticks[5];
    std::vector<SDL_Joystick*> joyStick;

    int mouseX, mouseY;
    unsigned int screenWidth, screenHeight;
    Uint32 delta;
    SDL_Window* templateWin;
    InputMap* inputMap;
    float moveSpeed;
    float mouseSensitivity;
};


#endif //WAHOO_INPUT_H
