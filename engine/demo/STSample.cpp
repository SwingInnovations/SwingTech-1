#include "../src/Math/STCore.h"
#include "../src/STGame.h"
#include "../src/STSceneManager.h"

class SampleState : public STGameState{
public:
    void init(STGame* window){
        auto scene = STSceneManager::Get()->initScene(getID());
        STGame::Get()->getCamera()->setSpeed(0.005f);
    }
    void update(STGame* game, stUint delta){

    }

    void render(STGame* win){

    }
};

int main(int argc, char** argv){

}