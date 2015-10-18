#include <iostream>

#include "src/STechWindow.h"
#include "src/SGameState.h"

using namespace std;

class TestState : public SGameState{
public:
    TestState(int id){ this->m_id = id; }
    void handleLogic(STechWindow* win, Uint32 delta){
        Input* input = win->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }
    }
};

int main(int argc, char** argv) {
    STechWindow window("TEST GAME", 1280, 720);
    window.setOpenGLVersion(3, 3);
    window.setTargetFPS(60);
    window.addState(new TestState(0));
    window.enterState(0);
    window.start();
}