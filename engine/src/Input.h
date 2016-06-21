#ifndef WAHOO_INPUT_H
#define WAHOO_INPUT_H

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_joystick.h"
#include "../include/SDL2/SDL_gamecontroller.h"
#include "Math/Vector.h"

#include <string>
#include <vector>
#include <c++/sstream>

#include "STGame.h"

class STGame;

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
        KEY_A = 0x04,
        KEY_B = 0x05,
        KEY_C = 0x06,
        KEY_D = 0x07,
        KEY_E = 0x08,
        KEY_F = 0x09,
        KEY_G = 0x0A,
        KEY_H = 0x0B,
        KEY_I = 0x0C,
        KEY_J = 0x0D,
        KEY_K = 0x0E,
        KEY_L = 0x0F,
        KEY_M = 0x10,
        KEY_N = 0x11,
        KEY_O = 0x12,
        KEY_P = 0x13,
        KEY_Q = 0x14,
        KEY_R = 0x15,
        KEY_S = 0x16,
        KEY_T = 0x17,
        KEY_U = 0x18,
        KEY_V = 0x19,
        KEY_W = 0x1A,
        KEY_X = 0x1B,
        KEY_Y = 0x1C,
        KEY_Z = 0x1D,

        KEY_1 = 0x1E,
        KEY_2 = 0x1F,
        KEY_3 = 0x20,
        KEY_4 = 0x21,
        KEY_5 = 0x22,
        KEY_6 = 0x23,
        KEY_7 = 0x24,
        KEY_8 = 0x25,
        KEY_9 = 0x26,
        KEY_0 = 0x27,

        KEY_ENTER = 0x28,
        KEY_RETURN = 0x28,
        KEY_ESC = 0x29,
        KEY_BACKSPACE = 0x2A,
        KEY_TAB = 0x2B,
        KEY_SPACE = 0x2C,

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
    int get(int target);
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
    Input(STGame * app, SDL_Event& e);
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
    void setDelta(Uint32 d){ delta = d; }

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