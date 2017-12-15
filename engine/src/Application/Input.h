#ifndef WAHOO_INPUT_H
#define WAHOO_INPUT_H

#include "../../include/SDL2/SDL.h"
#include "../../include/SDL2/SDL_joystick.h"
#include "../../include/SDL2/SDL_gamecontroller.h"
#include "../../include/json11/json11.hpp"
#include "../Math/Vector.h"

#include <string>
#include <vector>
#if __linux__
#include <sstream>
#else
#include <c++/sstream>
#endif

#include "STGame.h"

using namespace json11;


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
    enum Keys{
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

    inline int getTarget() const {
        return target;
    }

    inline void setTarget(int target) {
        this->target = target;
    }

    inline int getKey() const {
        return key;
    }

    inline void setKey(int key) {
        this->key = key;
    }

private:
    int target;
    int key;
};

class InputMap{
public:
    InputMap();

    /**
     * Loads Keyboard mapping info from a JSON File.
     * @param filePath JSON file containing input information.
     */
    explicit InputMap(const std::string& filePath);

    void addMapping(int target, int key);
    int get(int target);
    std::string info() {
        std::ostringstream ret;
        for (auto &i : mapping) {
            ret << "Target: " << i.getTarget() << " Key: " << i.getKey();
        }
        return ret.str();
    }
private:
    void initKeyMap();
    std::vector<InputKey> mapping;
    std::map<std::string, KEY::Keys> m_keyMap;
    std::map<std::string, int> m_movementMap;

};

class Input {

public:
    static Input* m_instance;
    Input();
    Input(STGame * app, SDL_Event& e);
    ~Input();
    
    void poll(SDL_Event&);
    inline void requestClose(){ closeRequested = true; }
    void setCursorVisible(bool);

    /** Centers cursor to window.
     *
     */
    void centerMouseInWindow();

    static Input* Get();
    static Input* Start(STGame* app, SDL_Event& e);

    inline void setInputMap(InputMap* map){ inputMap = map; }
    inline void setMoveSpeed(float speed){ moveSpeed = speed; }
    inline void setMouseSensitivity(float speed){ mouseSensitivity = speed; }
    inline void setCursorBound(bool v){ cursorBound = v; }
    inline InputMap* inputMapping(){ return inputMap; }


    template<typename T>  [[deprecated("Used the Non-templated Vector2f Function")]]
    Vector2<T> getMouseCoords(){
        T _x = (T)mouseX;
        T _y = (T)mouseY;
        Vector2<T> ret(_x, _y);
        return ret;
    }

    Vector2D GetMouseCoords(){
        return {(stReal)mouseX, (stReal)mouseY};
    }

    void addJoystick(int id);
    void addJoystick();
    void setDelta(Uint32 d){ delta = d; }

    bool isKeyDown(int);
    bool isKeyPressed(int);
    bool isMouseDown(int);
    bool isMousePressed(int);
    inline bool isCursorBound(){ return cursorBound; }
    inline bool isCloseRequested(){ return closeRequested; }

    inline float getMouseSensitivity()const{ return mouseSensitivity; }
    inline Uint32 getDelta()const{ return delta; }

    inline double getJoystickAxis(int joyIndex, int axis){
        return (double)SDL_JoystickGetAxis(joysticks[joyIndex], axis);
    }

    inline bool getJoystickButton(int joyIndex, int button){
        return SDL_JoystickGetButton(joysticks[joyIndex], button);
    }

    const char getInputCharacter()const;

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
    STGame* parent;
    InputMap* inputMap;
    float moveSpeed;
    float mouseSensitivity;
    char m_currentCharacter;
};


#endif //WAHOO_INPUT_H
