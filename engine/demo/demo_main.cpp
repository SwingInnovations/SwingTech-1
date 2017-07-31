#include "../src/Math/STCore.h"
#include "../src/STGame.h"
#include "../src/Entity/STEntity.h"
#include "../src/Graphics/GL/GLGraphics.h"
#include "../src/STSceneManager.h"

class InputMap;
class STGame;


using namespace std;

class STGraphicsComponent;

class TestState : public STGameState {
public:
    TestState(int id){ this->m_id = id; }

    void init(STGame * window) {
        counter = 0;
        drawMode = STMesh::TRIANGLES;
        auto scene = STSceneManager::Get()->initScene((stUint) getID());

        mat =  new STMaterial(new GLShader("standard"));
        auto resManager = window->getResourceManager();
        resManager->addMaterial("default",mat);
        GLGraphics::GlobalAmbient = Vector3<stReal>(.2,.2,.2);
        int count=0;
//
//        for (int i = 0; i< 5; i++) {
//            for(int j = 0; j< 5; j++) {
//
//                _testActors.push_back(new STActor("monkey.obj", STMesh::OBJ, resManager->getMaterial("default")));
//                _testActors.at(count)->setTranslateY(i *3 - 5.0f);
//                _testActors.at(count)->setTranslateX(j * 3 - 5.0f );
//                _testActors.at(count)->setShdrUniform("_Metallic", ((float)i)/4.0f);
//                _testActors.at(count)->setShdrUniform("_Roughness", ((float)j)/4.0f);
//                _testActors.at(count)->setScale(1);
//                scene->addActor(_testActors.at(count));
//                count++;
//            }
//         }
        STGame::Get()->getCamera()->setSpeed(0.005f);

        //auto actor = new STActor("sample.FBX", resManager->getMaterial("default")->copy());

        _testActor2 = new STActor("dice.obj");
        _testActor2->get<STGraphicsComponent>()->getMaterial()->setRoughness("Bronze_Roughness.jpg");
        _testActor2->transform()->setTranslateX(14.f);
        _testActor2->transform()->setRotationMode(Transform::RotationMode::Local);
        _testActor2->get<STEventComponent>()->addEvent("update", [](STEntity* self, STEntity* other){
            auto delta = STGame::Get()->getDelta();
            self->transform()->setRotateY(self->transform()->getRotateF().getY() + delta * 0.25f);
        });
        _testActor = new STActor("Chalice.fbx");
        _testActor->transform()->setTranslateY(1.f);
        _testActor->addComponent(typeid(STScriptComponent), new STScriptComponent("teapot.lua"));
        _testActor->get<STGraphicsComponent>()->getMaterial()->setDiffuseTexture("Bronze_Albedo.jpg");
        _testActor->get<STGraphicsComponent>()->getMaterial()->setMetallic("Bronze_Roughness.jpg");
        _testActor->get<STGraphicsComponent>()->getMaterial()->setRoughness("Bronze_Roughness.jpg");
        _plane = new STActor("plane.obj");
        _plane->get<STGraphicsComponent>()->getMaterial()->setRoughness(0.0);
        _plane->transform()->setTranslateY(1.f);
        _plane->setDiffuseTexture("checker.jpg");

        //_plane->setNormalTexture("testNormal.png");
        _plane->setTranslateY(-0.5f);

        _testLight = STLight::InitDirectionalLight(Vector3<stReal>(5.f, 5.f, -5.f), Vector3<stReal>(-.577f, .577f, -.577f), Vector3<stReal>(0.85f, 0.85f, 1.0f));
        _testLight->get<STLightComponent>()->getProperties()->intensity = 0.9f;
        _testLight->get<STLightComponent>()->setTarget(Vector3<stReal>(0.f, 0.f, 0.f));
        _testLight2 = STLight::InitDirectionalLight(Vector3<stReal>(4.f, 5.f, 4.f), Vector3<stReal>(.577f, .577f, .577f), Vector3<stReal>(0.f, 0.85f, .1f));
        _testLight3 = STLight::InitDirectionalLight(Vector3<stReal>(-4.f, 5.f, -3.f), Vector3<stReal>(.5, .5, .5), Vector3<stReal>(0.15, 0.15f, 0.15f));
        _testLight2->get<STLightComponent>()->getProperties()->useShadow = 0;
        _testLight2->get<STLightComponent>()->setTarget(Vector3<stReal>(0.f, 0.f, 0.f));
        _testLight3->get<STLightComponent>()->getProperties()->useShadow = 0;
        _testLight3->get<STLightComponent>()->setTarget(Vector3<stReal>(0.f, 0.f, 0.f));
        scene->addSkybox("green");

        scene->addActor(_testActor);
        scene->addActor(_testActor2);
        scene->addLight(_testLight2);
        scene->addLight(_testLight3);
        scene->addLight(_testLight);
        scene->addActor(_plane);
        STGraphics::ClearColor = Vector4<stReal>(0.0, 0.0, 0.168, 1.0);
    }

    void update(STGame* game, stUint delta){
        auto input = Input::Get();
        if(input->isKeyPressed(KEY::KEY_ESC)) input->requestClose();
        if(input->isKeyPressed(KEY::KEY_Q)){
            input->setCursorBound(!input->isCursorBound());
            input->setCursorVisible(!input->isCursorBound());
        }
        if(input->isKeyDown(KEY::KEY_O)){
            _testActor2->transform()->setTranslateZ(_testActor2->transform()->getTranslate().getZ() + 0.025f * delta);
        }
        if(input->isKeyDown(KEY::KEY_U)){
            _testActor2->transform()->setTranslateZ(_testActor2->transform()->getTranslate().getZ() - 0.025f * delta);
        }
        float c = counter * 0.05f;
        counter += 0.005f * delta;
        STSceneManager::Get()->getScene((stUint)getID())->update();
//        _testActor->update();
//        _testActor2->update();
//        _testActor2->transform()->setRotationMode(Transform::RotationMode::Local);
//        _testActor2->transform()->setRotateY(_testActor2->transform()->getRotateF().getY() + delta * 0.25f);
    }

    void render(STGame * win){
        auto grphx = win->getGraphics();
        win->getGraphics()->drawScene(STSceneManager::Get()->getScene((stUint)getID()));

    }

    ~TestState(){
        delete _testActor;
        delete _testActor2;
        delete _testLight;
        delete _testLight2;
        delete _testLight3;
    }
private:
    STSceneManager* sceneManager;
    int drawMode;
    int currObject;
    float counter = 0;
    STActor* _testActor;
    vector<STActor*> _testActors;
    STActor* _testActor2;
    STActor* _plane;
    STLight* _testLight;
    STLight* _testLight2;
    STLight* _testLight3;
    GLTexture* roughnessTex;
    STMaterial* mat;
    Vector3<stReal> lightPos;
    int width = 0, height = 0;
};


int main(int argc, char** argv){

    InputMap* inputMap = new InputMap;
    inputMap->addMapping(MOVEMENT::FORWARD, KEY::KEY_W);
    inputMap->addMapping(MOVEMENT::BACKWARD, KEY::KEY_S);
    inputMap->addMapping(MOVEMENT::STRAFE_LEFT, KEY::KEY_A);
    inputMap->addMapping(MOVEMENT::STRAFE_RIGHT, KEY::KEY_D);


    auto win = STGame::Init("Swing Tech 1", 1440, 720);
    win->setOpenGLVersion(4,0);
    win->setClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    win->setTargetFPS(120);
    STGraphics::YUp = false;
    win->getInput()->setInputMap(inputMap);
    win->addCamera(new Camera(*win, Vector3<stReal>(-1.5f, -.2f, 0.f), 0));
    win->addState(new TestState(0));
    win->enterState(0);
    win->getGraphics()->enableShadow(true);
    win->getGraphics()->setShadowResolution(512);
    win->getGraphics()->setRenderMode(STGraphics::DEFERRED);
    win->start();

    return 0;

}


