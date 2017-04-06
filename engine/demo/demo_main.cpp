#include "../src/Math/STCore.h"
#include "../src/STGame.h"
#include "../src/Entity/STEntity.h"
#include "../src/Graphics/GL/GLGraphics.h"
#include "../src/Entity/Components/STEventComponent.h"
#include "../src/Entity/STActor.h"
#include "../src/Graphics/Interface/STLabel.h"
#include "../src/Graphics/Interface/STButton.h"

class InputMap;
class STGame;


using namespace std;

class STGraphicsComponent;

class TestState : public STGameState {
public:
    TestState(int id){ this->m_id = id; }

    void init(STGame * window) {
        //window->getCamera()->setHAngle(90.0f);
        counter = 0;
        drawMode = STMesh::TRIANGLES;
        auto scene = STSceneManager::Get()->initScene((stUint) getID());

        mat =  new STMaterial(new GLShader("standard"));
        auto resManager = window->getResourceManager();
        resManager->addMaterial("default",mat);
        //  resManager->addMaterial("def", new STMaterial(new GLShader("standard")));
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

        _testActor2 = new STActor("teapot.obj", resManager->getMaterial("default"));
        //_testActor2->setTranslateX(1);
        _testActor2->setShdrUniform("_Metallic", 0.0f);
        _testActor2->setShdrUniform("_Roughness",0.0f);
        _testActor2->setScale(0.01);
        _testActor2->setDiffuseTexture("grid.png");
        _testActor2->setNormalTexture("testNormal.png");
        mat->setBaseColor(Vector3<stReal>(.7,.7,.7));
        //  _testActor2->setRotateX(90);
        // _testActor2->setRotateY(90);
        _testActor = new STActor("dice.obj", resManager->getMaterial("default"));
        _testActor->setShdrUniform("_Metallic", 0.f);
        _testActor->setShdrUniform("_Roughness", 0.f);
        _testActor->setDiffuseTexture("grid.png");
        _testActor->setNormalTexture("testNormal.png");
        _testActor->setTranslateX(2.f);
        _testActor->setTranslateZ(-2.f);

        _plane = new STActor("plane.obj", resManager->getMaterial("default"));
        _plane->setShdrUniform("_Metallic", 0.f);
        _plane->setShdrUniform("_Roughness", 1.f);
        _plane->setDiffuseTexture("grid.png");
        //_plane->setNormalTexture("testNormal.png");
        _plane->setTranslateY(-0.5f);

        //  roughnessTex = new GLTexture("roughness.png");

//        mat->setDiffuseTexture("sampledDiffuseColor.png");
//        mat->setNormalTexture("testNormal.png");

        //_testActor2->setShdrUniform_Texture("_RoughnessTex",roughnessTex->genTex("roughness.png"));
        //_testActor2->setTranslateY(-4);
//        _testLight = new STLight(Vector3<stReal>(-1,-1,-1),Vector3<stReal>(1,1,1));
//        _testLight->intensity =2.5;
//        _testLight->radius=-1;
//        _testLight = STLight::DirectionalLight(Vector3<stReal>(-2.f, 3.f, -7.f), Vector3<stReal>(-5.f, 3.f, -5.f) - Vector3<stReal>(0.f, 0.f, 0.f), Vector3<stReal>(1.0f, 0.f, 0.f));
//        _testLight->intensity = 0.5f;
//        _testLight->radius = -1;
        _testLight = STLight::InitDirectionalLight(Vector3<stReal>(-2.f, 3.f, -7.f), Vector3<stReal>(-5.f, 3.f, -5.f) - Vector3<stReal>(0.f, 0.f, 0.f), Vector3<stReal>(1.0f, 0.f, 0.f));
        // _testLight->setTranslateZ(2);
        _testLight2 = STLight::InitDirectionalLight(Vector3<stReal>(5.f, -3.f, 5.f),Vector3<stReal>(0.f, 0.f, 0.f) - Vector3<stReal>(5.f, 3.f, 5.f), Vector3<stReal>(1.f, 1.f, 1.f));

//        _testLight2 = STLight::DirectionalLight(Vector3<stReal>(5.f, 3.f, 5.f), Vector3<stReal>(5.f, 3.f, 5.f) - Vector3<stReal>(0.f, 0.f, 0.f), Vector3<stReal>(1.f, 1.f, 1.f));
//        _testLight2->intensity =0.5f;
//        _testLight2->radius=-1;

        scene->addSkybox("mystic", "skybox");


        // scene->addLight(_testLight);

        scene->addActor(_testActor2);
        scene->addActor(_testActor);
        scene->addLight(_testLight2);
        scene->addActor(_plane);
        //scene->addLight(_testLight);
        STGraphics::ClearColor = Vector4<stReal>(0.0, 0.0, 0.168, 1.0);
    }

    void update(STGame* game, stUint delta){
        auto input = Input::Get();
        if(input->isKeyPressed(KEY::KEY_ESC)) input->requestClose();
        if(input->isKeyPressed(KEY::KEY_Q)){
            input->setCursorBound(!input->isCursorBound());
        }
        _testActor->setRotateY(counter);
        counter++;
    }

    void render(STGame * win){
        auto grphx = win->getGraphics();
        win->getGraphics()->drawScene(STSceneManager::Get()->getScene((stUint)getID()));
        //_testActor2->draw();

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
    STButton* btn;
    STActor* _testActor;
    vector<STActor*> _testActors;
    STActor* _testActor2;
    STActor* _plane;
    STLight* _testLight;
    STLight* _testLight2;
    STLight* _testLight3;
    GLTexture* roughnessTex;
    STMaterial* mat;
    STLabel* lbl;
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
    Vector3<stReal> campos(0.0, 0, 3.0f);
    win->addCamera(new Camera(*win, campos, 0));
    win->addState(new TestState(0));
    win->enterState(0);
    win->start();

    return 0;

}


