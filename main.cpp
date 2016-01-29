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
        counter = 0;
        float verts[] = { 0.5f, 0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f,
                            -0.5f, -0.5f, 0.0f,
                            -0.5, 0.5, 0.0f};
        int vSize = sizeof(verts)/sizeof(verts[0]);
        float tex[] = { 0.0f, 0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                            -0.5f, 0.5f, 0.0f};
        int tSize = sizeof(tex)/sizeof(tex[0]);
        int ind[] = { 0, 1, 2, 2, 3, 0 };
        int iSize = sizeof(ind)/ sizeof(ind[0]);

        R = 0.0f;
        G = 0.0f;
        B = 0.0f;

        _entity = new STEntity();
        _entity->addComponent(typeid(STMeshComponent), new STMeshComponent(verts, vSize, tex, tSize, ind, iSize));
        _entity->addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new GLShader("basic")));
        _entity->get<STGraphicsComponent>()->addShdrAttrib("uniR", R);
        _entity->get<STGraphicsComponent>()->addShdrAttrib("uniG", G);
        _entity->get<STGraphicsComponent>()->addShdrAttrib("uniB", B);
    }

    void handleLogic(STechWindow* win, Uint32 delta){

        Input* input = win->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }
        if(input->isKeyDown(KEY::KEY_Y)){
            R += 0.0025f * delta;
            _entity->get<STGraphicsComponent>()->setShdrAttrib("uniR", R);
        }

        if(input->isKeyDown(KEY::KEY_H)){
            R -= 0.0025f * delta;
            _entity->get<STGraphicsComponent>()->setShdrAttrib("uniR", R);
        }

        if(input->isKeyDown(KEY::KEY_U)){
            G += 0.0025f * delta;
            _entity->get<STGraphicsComponent>()->setShdrAttrib("uniG", G);
        }

        if(input->isKeyDown(KEY::KEY_J)){
            G -= 0.0025f * delta;
            _entity->get<STGraphicsComponent>()->setShdrAttrib("uniG", G);
        }

        if(input->isKeyDown(KEY::KEY_I)) {
            B += 0.0025f * delta;
            _entity->get<STGraphicsComponent>()->setShdrAttrib("uniB", B);
        }

        if(input->isKeyDown(KEY::KEY_K)) {
            B -= 0.0025f * delta;
            _entity->get<STGraphicsComponent>()->setShdrAttrib("uniB", B);
        }

        counter += sin(0.025f * delta);
        _entity->transform()->setTranslateX(counter);
        std::cout << "Y Rotation: " << _entity->transform()->getRotate<stReal>().getY() << std::endl;
    }

    void render(STechWindow* win){
        _entity->draw(win->getCamera());
    }

private:
    float counter;
    STEntity* _entity;
    float R;
    float G;
    float B;
};

int main(int argc, char** argv) {
    STechWindow window("TEST GAME", 1280, 720);
    window.setOpenGLVersion(3, 3);
    window.setTargetFPS(60);
    Vector3<stReal> camPos(0.0f, 0.0f, 0.0f);
    window.addCamera(new Camera(window, camPos, 0));
    window.addState(new TestState(0));
    window.enterState(0);
    window.setClearColor(Vector4<stReal>(0.0f, 0.0f, 0.14f, 1.0f));
    window.start();
}