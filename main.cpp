#include <iostream>

#include "src/Math/STech_Core.h"
#include "src/STechWindow.h"
#include "src/SGameState.h"
#include "src/STEntity.h"
#include "src/Graphics/GL/GLShader.h"
#include "src/STGraphicsComponent.h"


using namespace std;

class STGraphicsComponent;


class TestState : public SGameState{
public:
    TestState(int id){ this->m_id = id; }

    void init(STechWindow* window){
        window->getCamera()->setHAngle(-135.0f);
        counter = 0;
        drawMode = STMesh::TRIANGLES;

        lightPos = Vector3<stReal>(1.0f, 1.0f, -1.0f);


        _ball = new STEntity("box.obj", STMesh::OBJ, new GLShader("objShdr"), new GLTexture("grid.png"));
        _ball->get<STGraphicsComponent>()->addShdrAttrib("lightPos", lightPos);
        _ball->transform()->setTranslate(-2.0f);

        //light Color
        _box2 = new STEntity("sphere.obj", STMesh::OBJ, "lightSource");
        _box2->get<STGraphicsComponent>()->addShdrAttrib("objColor", Vector3<stReal>(1.0f, 1.0f, 1.0f));
        _box2->transform()->setTranslateX(1.0f);
        _box2->transform()->setTranslateY(2.0f);
        _box2->transform()->setTranslateZ(-1.0f);
        _box2->transform()->setScaleX(0.5f);
        _box2->transform()->setScaleY(0.5f);
        _box2->transform()->setScaleZ(0.5f);

        _box1 = new STEntity("box.obj", STMesh::OBJ, "basic");
        _box1->get<STGraphicsComponent>()->addShdrAttrib("objColor", Vector3<stReal>(1.0f, 0.5f, 0.31f));
        _box1->get<STGraphicsComponent>()->addShdrAttrib("lightPos", _box2->transform()->getTranslate<stReal>());


        std::cout << "Box1 Mesh: " << _box1->get<STMeshComponent>()->getFileName() << std::endl;
        std::cout << "Box1 Shader: " << _box1->get<STGraphicsComponent>()->shdr()->getShaderName() << std::endl;
        std::cout << "Box2 Mesh: " << _box2->get<STMeshComponent>()->getFileName() << std::endl;
        std::cout << "Box2 Shader: " << _box2->get<STGraphicsComponent>()->shdr()->getShaderName() << std::endl;
    }

    void handleInput(STechWindow* win, Uint32 delta){
        Input* input = win->getInput();
        input->setCursorBound(false);
        input->setCursorBound(true);

        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }

        if(input->isKeyPressed(KEY::KEY_6)) currObject = 0;

        if(input->isKeyPressed(KEY::KEY_7)) currObject = 1;

        if(input->isKeyPressed(KEY::KEY_0)){
            win->getCamera()->centerCam(input);
        }
    }

    void handleLogic(STechWindow* win, Uint32 delta){
        counter += 0.0025f * delta;
        _box1->transform()->setRotateY(counter);
        _box2->transform()->setRotateY(-counter);
    }

    void render(STechWindow* win){
//        if(currObject == 0) _entity->draw(win->getCamera(), drawMode);
//        else if(currObject == 1) _ball->draw(win->getCamera(), drawMode);
//        else std::cout << "Not Drawing" << std::endl;
        _box1->draw(win->getCamera());
        _box2->draw(win->getCamera());
        _ball->draw(win->getCamera());
    }

private:
    int drawMode;
    int currObject;
    float counter = 0;
    STEntity* _entity;
    STEntity* _ball;
    STEntity* _box1;
    STEntity* _box2;
    Vector3<stReal> lightPos;
};

int main(int argc, char** argv) {
    STechWindow window("WAHOO Demo", 1440, 720);
    window.setOpenGLVersion(3, 3);
    window.setTargetFPS(60);
    Vector3<stReal> camPos(-3.0f, 0.0f, 3.0f);
    window.addCamera(new Camera(window, camPos, 0));
    window.addState(new TestState(0));
    window.enterState(0);
    window.setClearColor(Vector4<stReal>(0.0f, 0.0f, 0.14f, 1.0f));
    window.start();
}