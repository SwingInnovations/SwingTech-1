#include <iostream>

#include "src/Math/STech_Core.h"
#include "src/STechWindow.h"
#include "src/SGameState.h"
#include "src/STEntity.h"
#include "src/Graphics/GL/GLShader.h"

using namespace std;

class TestState : public SGameState{
public:
    TestState(int id){ this->m_id = id; }

    void init(STechWindow* window){
        float verts[] = { 0.0f, 0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f,
                            -0.5f, -0.5f, 0.0f};
        int vSize = sizeof(verts)/sizeof(verts[0]);
        float tex[] = { 0.0f, 0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f};
        int tSize = sizeof(tex)/sizeof(tex[0]);
        int ind[] = { 0, 1, 2 };
        int iSize = sizeof(ind)/ sizeof(ind[0]);

        _entity = new STEntity();
        _entity->addComponent(std::type_index(typeid(STMeshComponent)), new STMeshComponent(verts, vSize, tex, tSize, ind, iSize));
        //_entity->addComponent(std::type_index(typeid(STMeshComponent)), new STMeshComponent("box.obj", STMesh::OBJ));
        _entity->addComponent(std::type_index(typeid(STGraphicsComponent)), new STGraphicsComponent(new GLShader("basic")));
    }

    void handleLogic(STechWindow* win, Uint32 delta){
        Input* input = win->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }
    }

    void render(STechWindow* win){

        _entity->draw(win->getCamera());
    }
private:
    STEntity* _entity;
};

int main(int argc, char** argv) {
    STechWindow window("TEST GAME", 1280, 720);
    window.setOpenGLVersion(3, 3);
    window.setTargetFPS(60);
    Vector3<stReal> camPos(0.0f, 0.0f, 0.0f);
    window.addCamera(new Camera(window, camPos, 0));
    window.addState(new TestState(0));
    window.enterState(0);
    window.setClearColor(Vector4<stReal>(0.0f, 0.0f, 0.0f, 1.0f));
    window.start();
}