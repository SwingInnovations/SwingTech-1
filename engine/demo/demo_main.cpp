#include "../src/STGlobal.h"
#include "../src/Input.h"

class InputMap;
class STGame;

int main(int argc, char** argv){
    InputMap* inputMap = new InputMap;
    inputMap->addMapping(MOVEMENT::FORWARD, KEY::KEY_A);
    inputMap->addMapping(MOVEMENT::BACKWARD, KEY::KEY_S);
    inputMap->addMapping(MOVEMENT::STRAFE_LEFT, KEY::KEY_A);
    inputMap->addMapping(MOVEMENT::STRAFE_RIGHT, KEY::KEY_D);

    STGame game("SwingTech1", 1440, 900);
    game.setOpenGLVersion(3, 3);
    game.setTargetFPS(120);
    game.getInput()->setInputMap(inputMap);
    Vector3<stReal> camPos(0.0f, -0.2f, -5.0f);
    game.addCamera(new Camera(game, camPos, 0));
    game.start();
    return 0;
}

