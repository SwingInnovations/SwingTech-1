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
        counter2 = 0;
        currObject = 0;
        drawMode = STMesh::TRIANGLES;
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

        window->getCamera()->setHAngle(216.0f);

        counter3 = 0.0f;

        lightPos = Vector3<stReal>(1.0f, 1.0f, -1.0f);

        _entity = new STEntity();
        //_entity->addComponent(typeid(STMeshComponent), new STMeshComponent(verts, vSize, tex, tSize, ind, iSize));
        _entity->addComponent(typeid(STMeshComponent), new STMeshComponent("box.obj", STMesh::OBJ));
        _entity->addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new GLShader("basic"), new GLTexture("grid.png")));
        _entity->get<STGraphicsComponent>()->addShdrAttrib("lightPos", lightPos);

        _ball = new STEntity();
        _ball->addComponent(typeid(STMeshComponent), new STMeshComponent("sphere.obj", STMesh::OBJ));
        _ball->addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new GLShader("basic"), new GLTexture("grid.png")));
        _ball->get<STGraphicsComponent>()->addShdrAttrib("lightPos", lightPos);
        _ball->transform()->setScaleX(2.0f);
        _ball->transform()->setScaleY(2.0f);
        _ball->transform()->setScaleZ(2.0f);
    }

    void handleInput(STechWindow* win, Uint32 delta){
        Input* input = win->getInput();
        input->setCursorBound(false);
        input->setCursorBound(true);

        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }

        if(input->isKeyPressed(KEY::KEY_1)){
            drawMode = STMesh::TRIANGLES;
        }
        if(input->isKeyPressed(KEY::KEY_2)){
            drawMode = STMesh::LINES;
        }
        if(input->isKeyPressed(KEY::KEY_3)){
            drawMode = STMesh::LINE_LOOP;
        }

        if(input->isKeyPressed(KEY::KEY_6)){
            currObject = 0;
        }

        if(input->isKeyPressed(KEY::KEY_7)){
            currObject = 1;
        }

        if(input->isKeyDown(KEY::KEY_A)){
            stReal _x = win->getCamera()->transform()->getTranslate<stReal>().getX();
            _x += 0.0025f * delta;
            win->getCamera()->transform()->setTranslateX(_x);
        }

        if(input->isKeyDown(KEY::KEY_D)){
            stReal _x = win->getCamera()->transform()->getTranslate<stReal>().getX();
            _x -= 0.0025f * delta;
            win->getCamera()->transform()->setTranslateX(_x);
        }

        if(input->isKeyPressed(KEY::KEY_0)){
            win->getCamera()->centerCam(input);
        }
    }

    void handleLogic(STechWindow* win, Uint32 delta){
        counter += 0.0025f * delta;
        _entity->transform()->setRotateY(counter);
        _ball->transform()->setRotateY(counter);
    }

    void render(STechWindow* win){
        if(currObject == 0) _entity->draw(win->getCamera(), drawMode);
        else if(currObject == 1)_ball->draw(win->getCamera(), drawMode);
        else std::cout << "Not Drawing Object " << std::endl;

    }

private:
    int drawMode;
    int currObject;
    float counter;
    float counter2;
    float counter3;
    STEntity* _entity;
    STEntity* _ball;
    Vector3<stReal> lightPos;
    float R;
    float G;
    float B;
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