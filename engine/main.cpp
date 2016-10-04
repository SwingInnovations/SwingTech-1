#include <iostream>

#include "src/Math/STCore.h"
#include "src/STGame.h"
#include "src/Entity/STEntity.h"
#include "src/Graphics/GL/GLGraphics.h"
#include "src/Entity/Components/STEventComponent.h"
#include "src/Entity/STActor.h"
#include "src/Graphics/Interface/STLabel.h"
#include "src/Graphics/Interface/STButton.h"


using namespace std;

class STGraphicsComponent;

class TestState : public STGameState {
public:
    TestState(int id){ this->m_id = id; }

    void init(STGame * window){
        //window->getCamera()->setHAngle(90.0f);
        counter = 0;
        drawMode = STMesh::TRIANGLES;
        auto scene = STSceneManager::Get()->initScene((stUint)getID());

        lightPos = Vector3<stReal>(1.0f, 1.0f, -1.0f);

        auto resManager = window->getResourceManager();
        resManager->addMaterial("lit", new STMaterial(new GLShader("lightSource")));

        _testActor = new STActor("tower.obj", resManager->getMaterial("lit"));
        _testActor->addShdrUniform("objColor", Vector3<stReal>(1.0, 0.5, 0.31f));
        _testActor->get<STEventComponent>()->inputEvent([](STEntity* self){
            auto input = Input::Get();
            if(input->isKeyPressed(KEY::KEY_SPACE)){
                self->setVisible(false);
                self->setShdrUniform("objColor", Vector3<stReal>(0.0, 0.2, 0.88));
            }
        });

        lbl = new STLabel(0, 32, "SwingTech 1 - Indev");
        lbl->setFontColor(STColor(GREEN));

        btn = new STButton("Quit");
        btn->setFontColor(STColor(MAGENTA));
        int btnWidth = (int)btn->get<STRectBoundsComponent>()->bounds()->getWidth();
        btn->setPosition(Vector2<stReal>(STGame::RES_WIDTH - btnWidth, 32));
        btn->inputEvent([](STEntity* self){
            auto input = Input::Get();
            if(input->isMousePressed(1)){
                input->requestClose();
            }
        });

        scene->addSkybox("green", "skybox");
        scene->addActor(_testActor);
        STGraphics::ClearColor = Vector4<stReal>(0.0, 0.0, 0.168, 1.0);
    }

    void handleInput(STGame * win, Uint32 delta){
        Input* input = win->getInput();
        auto cam = win->getCamera();
        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }

        if(input->isKeyPressed(KEY::KEY_Q)){
            bool state = input->isCursorBound();
            input->setCursorBound(!state);
            input->setCursorVisible(state);
        }

        if(input->isKeyPressed(KEY::KEY_6)) currObject = 0;

        if(input->isKeyPressed(KEY::KEY_7)) currObject = 1;

        if(input->isKeyPressed(KEY::KEY_0)){
            win->getCamera()->centerCam(input);
        }
    }

    void handleLogic(STGame * win, Uint32 delta){
        lbl->update(win);
        btn->update(win);
        _testActor->update();
        counter += 0.025f * delta;
    }

    void render(STGame * win){
        auto grphx = win->getGraphics();
        win->getGraphics()->drawScene(STSceneManager::Get()->getScene((stUint)getID()));
        lbl->draw(grphx);
        btn->draw(grphx);
    }

    ~TestState(){
        delete _testActor;
        delete btn;
        delete lbl;
    }
private:
    STSceneManager* sceneManager;
    int drawMode;
    int currObject;
    float counter = 0;
    STButton* btn;
    STActor* _testActor;
    STLabel* lbl;
    Vector3<stReal> lightPos;
    int width = 0, height = 0;
};

int main(int argc, char** argv) {

    InputMap* inputMap = new InputMap;
    inputMap->addMapping(MOVEMENT::FORWARD, KEY::KEY_W);
    inputMap->addMapping(MOVEMENT::BACKWARD, KEY::KEY_S);
    inputMap->addMapping(MOVEMENT::STRAFE_LEFT, KEY::KEY_A);
    inputMap->addMapping(MOVEMENT::STRAFE_RIGHT, KEY::KEY_D);

    auto win = STGame::Init("Swing Tech 1", 1440, 720);
    win->setOpenGLVersion(3, 3);
    win->setTargetFPS(120);
    STGraphics::YUp = false;
    win->getInput()->setInputMap(inputMap);
    Vector3<stReal> campos(0.0, -0.2f, -5.0f);
    win->addCamera(new Camera(*win, campos, 0));
    win->addState(new TestState(0));
    win->enterState(0);
    win->setClearColor(Vector4<stReal>(0.0f, 0.0f, 0.14f, 1.0f));
    win->start();

    return 0;
}