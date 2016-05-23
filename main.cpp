#include <iostream>

#include "src/Math/STCore.h"
#include "src/STGame.h"
#include "src/SGameState.h"
#include "src/STEntity.h"
#include "src/Graphics/GL/GLShader.h"
#include "src/Graphics/GL/GLGraphics.h"
#include "src/STGraphicsComponent.h"
#include "src/Math/Shape/Rect.h"
#include "src/STSceneManager.h"


using namespace std;

class STGraphicsComponent;

class TestState : public SGameState{
public:
    TestState(int id){ this->m_id = id; }

    void init(STGame * window){
        window->getCamera()->setHAngle(90.0f);
        counter = 0;
        drawMode = STMesh::TRIANGLES;
        sceneManager = new STSceneManager();

        lightPos = Vector3<stReal>(1.0f, 1.0f, -1.0f);

        auto resManager = window->getResourceManager();
        resManager->addShader("basic", new GLShader("basic"));
        resManager->addTexture("grid", new GLTexture("grid.png"));
        resManager->addShader("lightSource", new GLShader("lightSource"));
        resManager->addShader("screen", new GLShader("screen"));
        resManager->addShader("objShdr", new GLShader("objShdr"));
        resManager->addShader("rectShdr", new GLShader("rectShdr"));
        resManager->addMaterial("basic", new STMaterial(new GLShader("basic"), new GLTexture("grid.png")));

        //light Color
        _box2 = new STEntity("sphere.obj", STMesh::OBJ, resManager->getShader("lightSource"));
        _box2->get<STGraphicsComponent>()->addShdrUniform("objColor", Vector3<stReal>(1.0f, 0.5f, 0.0f));
        _box2->setTranslateY(5.0f);
        _box2->setTranslateX(12.0f);
        _box2->setScale(0.5f);

        _box1 = new STEntity("sphere.obj", STMesh::OBJ, resManager->getMaterial("basic"));
        //_box1 = new STEntity("sphere.obj", STMesh::OBJ, resManager->getShader("basic"), resManager->getTexture("grid"));
        _box1->addShdrUniform("objColor", Vector3<stReal>(1.0, 0.5f, 0.31f));
        _box1->addShdrUniform("lightPos", _box2->transform()->getTranslate<stReal>());
        _box1->addShdrUniform("lightColor", Vector3<stReal>(1.0f, 0.5f, 0.0f));
        _box1->setScale(3.0f);
        _box1->addScriptComponent("test.lua");

        _ball = new STEntity("sphere.obj", STMesh::OBJ, resManager->getShader("basic"), resManager->getTexture("grid"));
        _ball->setTranslateX(-1.0f);
        _ball->setTranslateZ(-1.0f);
        _ball->addShdrUniform("lightPos", _box2->transform()->getTranslate<stReal>());
        _ball->addShdrUniform("lightColor", Vector3<stReal>(1.0f, 0.5f, 0.0f));
        _ball->setScale(3.0f);
        std::cout << "Now loading skybox! "<< std::endl;

        sceneManager->addSkyBox("green", "skybox");
        sceneManager->addEntity(_box2);
        sceneManager->addEntity(_box1);
        sceneManager->addEntity(_ball);
        STGraphics::ClearColor = Vector4<stReal>(0.0, 0.0, 0.168, 1.0);
        ((GLGraphics*)window->getGraphics())->addRenderPass(sceneManager,(GLShader*)resManager->getShader("screen"));
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
        counter += 0.025f * delta;
        _box2->transform()->setRotateY(-counter);
        _box2->setTranslateY(5.0f * sin(counter * 0.01f));
        _box1->setRotateY(counter);
        _box1->get<STGraphicsComponent>()->setShdrUniform("lightPos", _box2->transform()->getModel().toVector4().toVector3Norm());
        _ball->setShdrUniform("lightPos", _box2->transform()->getModel().toVector4().toVector3Norm());
    }

    void render(STGame * win){
        auto grphx = win->getGraphics();
        win->getGraphics()->drawScene(sceneManager);
        GLGraphics::TextColor = Vector3<stReal>(1.0, 1.0, 1.0);
        win->getGraphics()->drawText(Vector2<stReal>(0, 32), "Renderer: " + grphx->getVendor(), 32);
    }

    ~TestState(){
        delete _box1;
        delete _box2;
        delete _ball;
    }
private:
    STSceneManager* sceneManager;
    int drawMode;
    int currObject;
    float counter = 0;
    STEntity* _box1;
    STEntity* _box2;
    STEntity* _ball;
    Vector3<stReal> lightPos;
};

int main(int argc, char** argv) {

    InputMap* inputMap = new InputMap;
    inputMap->addMapping(MOVEMENT::FORWARD, KEY::KEY_W);
    inputMap->addMapping(MOVEMENT::BACKWARD, KEY::KEY_S);
    inputMap->addMapping(MOVEMENT::STRAFE_LEFT, KEY::KEY_A);
    inputMap->addMapping(MOVEMENT::STRAFE_RIGHT, KEY::KEY_D);

    STGame window("WAHOO Demo", 1440, 720);
    window.setOpenGLVersion(3, 3);
    window.setTargetFPS(120);
    window.getInput()->setInputMap(inputMap);
    Vector3<stReal> camPos(-0.0f, -0.2f, -5.0f);
    window.addCamera(new Camera(window, camPos, 0));
    window.addState(new TestState(0));
    window.enterState(0);
    window.setClearColor(Vector4<stReal>(0.0f, 0.0f, 0.14f, 1.0f));
    window.start();
}