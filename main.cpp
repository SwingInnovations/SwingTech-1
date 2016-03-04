#include <iostream>

#include "src/Math/STCore.h"
#include "src/STGame.h"
#include "src/SGameState.h"
#include "src/STEntity.h"
#include "src/Graphics/GL/GLShader.h"
#include "src/STGraphicsComponent.h"
#include "src/Math/Shape/Rect.h"


using namespace std;

class STGraphicsComponent;


class TestState : public SGameState{
public:
    TestState(int id){ this->m_id = id; }

    void init(STGame * window){
        window->getCamera()->setHAngle(-135.0f);
        counter = 0;
        drawMode = STMesh::TRIANGLES;

        lightPos = Vector3<stReal>(1.0f, 1.0f, -1.0f);

        //light Color
        _box2 = new STEntity("box.obj", STMesh::OBJ, "lightSource");
        _box2->get<STGraphicsComponent>()->addShdrAttrib("objColor", Vector3<stReal>(1.0f, 1.0f, 1.0f));
        _box2->transform()->setTranslateY(7.0f);
        _box2->transform()->setTranslateX(6.0f);
        _box2->transform()->setScaleX(0.5f);
        _box2->transform()->setScaleY(0.5f);
        _box2->transform()->setScaleZ(0.5f);

        _box1 = new STEntity("human.obj", STMesh::OBJ, "basic", "grid.png");
        _box1->get<STGraphicsComponent>()->addShdrAttrib("objColor", Vector3<stReal>(1.0f, 0.5f, 0.31f));
        _box1->get<STGraphicsComponent>()->addShdrAttrib("lightPos", _box2->transform()->getTranslate<stReal>());
        _box1->transform()->setScale(0.1f);

        plane = new STEntity();
        plane->addComponent(typeid(STMeshComponent), new STMeshComponent(new SWRect(Vector2<stReal>(0, 0), Vector2<stReal>(386, 512))));
        plane->addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new GLShader("sample")));
    }

    void handleInput(STGame * win, Uint32 delta){
        Input* input = win->getInput();
        auto cam = win->getCamera();
        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }

        if(input->isKeyDown(KEY::KEY_S)){

        }

        if(input->isKeyPressed(KEY::KEY_Q)){
            bool state = input->isCursorBound();
            input->setCursorBound(!state);
            input->setCursorVisible(!state);
        }

        if(input->isKeyPressed(KEY::KEY_6)) currObject = 0;

        if(input->isKeyPressed(KEY::KEY_7)) currObject = 1;

        if(input->isKeyPressed(KEY::KEY_0)){
            win->getCamera()->centerCam(input);
        }
    }

    void handleLogic(STGame * win, Uint32 delta){
        counter += 0.025f * delta;
        _box1->transform()->setRotateY(counter);
        _box2->transform()->setRotateY(-counter);
        _box1->get<STGraphicsComponent>()->setShdrAttrib("lightPos", _box2->transform()->getTranslate<stReal>());
    }

    void render(STGame * win){
        _box1->draw(win->getCamera());
        _box2->draw(win->getCamera());
        plane->draw(win->getCamera());
    }

    ~TestState(){
        delete _box1;
        delete _box2;
    }
private:
    int drawMode;
    int currObject;
    float counter = 0;
    STEntity* plane;
    STEntity* _box1;
    STEntity* _box2;
    Vector3<stReal> lightPos;
};

int main(int argc, char** argv) {
    STGame window("WAHOO Demo", 1440, 720);
    window.setOpenGLVersion(3, 3);
    window.setTargetFPS(60);
    Vector3<stReal> camPos(-0.0f, -0.0f, 2.0f);
    window.addCamera(new Camera(window, camPos, 0));
    window.addState(new TestState(0));
    window.enterState(0);
    window.setClearColor(Vector4<stReal>(0.0f, 0.0f, 0.14f, 1.0f));
    window.getInput()->setCursorBound(true);
    window.start();
}