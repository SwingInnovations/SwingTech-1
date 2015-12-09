#include <iostream>

#include "src/STechWindow.h"
#include "src/SGameState.h"
#include "src/STEntity.h"
#include "src/Graphics/GL/GLShader.h"

using namespace std;

class TestState : public SGameState{
public:
    TestState(int id){ this->m_id = id; }
    void init(STechWindow* window){
        _entity = new STEntity();
        _entity->addComponent(std::type_index(typeid(STMeshComponent)), new STMeshComponent("box.obj", STMesh::OBJ));
        _entity->addComponent(std::type_index(typeid(STGraphicsComponent)), new STGraphicsComponent(new GLShader("basic")));
    }

    void handleLogic(STechWindow* win, Uint32 delta){
        Input* input = win->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)){
            input->requestClose();
        }
    }

    void render(STechWindow* win){
        _entity->draw();
    }
private:
    STEntity* _entity;
};

int main(int argc, char** argv) {
    STechWindow window("TEST GAME", 1280, 720);
    window.setOpenGLVersion(3, 3);
    window.setTargetFPS(60);
    window.addState(new TestState(0));
    window.enterState(0);
    window.setClearColor(Vector4<stReal>(0.2f, 0.2f, 0.4f, 1.0f));
    window.start();
}