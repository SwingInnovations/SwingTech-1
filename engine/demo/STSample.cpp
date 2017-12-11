#include "../src/Math/STCore.h"
#include "../src/Application/STGame.h"
#include "../src/Application/STSceneManager.h"
#include "../src/Application/Util/STJson.h"

/**
 * This is an example class for demonstrating How a typical game state would be setup.
 */
class SampleState : public STGameState{
public:
    SampleState(stInt id){ m_id = id; }
    void init(STGame* game) override {
        m_scene->addSkybox("green");
        game->getCamera()->setSpeed(0.025f);

        auto mainLight = STLight::InitDirectionalLight(Vector3D(4.f, 5.f, 3.f), Vector3D(-.5f, -.5f, -.5f), Vector3D(0.25f, 0.25f, 0.85f));
        mainLight->get<STLightComponent>()->setTarget(Vector3D(0.f, 0.f, 0.f));

        auto accentLight = STLight::InitDirectionalLight(Vector3D(2.f, 4.f, -3.f), Vector3D(), Vector3D(1.f, 1.f, 1.f));
        accentLight->get<STLightComponent>()->setTarget(Vector3D());

        auto character = new STActor("animCylinder.fbx");
        //character->get<STGraphicsComponent>()->getMaterial()->setRoughness("Bronze_Roughness.jpg");
//        character->get<STGraphicsComponent>()->getMaterial()->setDiffuseColor(STColor(BLUE));
//        character->get<STGraphicsComponent>()->getMaterial()->setMetallic(0.1f);
        character->addComponent(typeid(STScriptComponent), new STScriptComponent("Suzanne_Control.lua"));
        character->setAttribute("speedFactor", 0.025f);
        character->transform()->setRotateX(-90);
        character->transform()->setRotationMode(Transform::Local);

        auto diceBox = new STActor("dice.obj");
        diceBox->get<STGraphicsComponent>()->getMaterial()->setMetallic(1.f);
        diceBox->get<STGraphicsComponent>()->getMaterial()->setDiffuseColor(STColor(RED));
        diceBox->transform()->setTranslateX(1.0f);
        diceBox->transform()->setTranslateZ(2.f);

        auto characterTransform = character->transform()->to_json().dump();
        auto newTransform = Transform::FromJson(characterTransform);

        auto plane = new STActor("plane.obj");
        plane->transform()->setTranslateY(-0.5f);
        plane->get<STGraphicsComponent>()->setDiffuseTexture("grid.png");
        m_scene->addLight(mainLight);
        m_scene->addLight(accentLight);
        m_scene->addActor(character);
        m_scene->addActor(diceBox);
        m_scene->addActor(plane);
        counter = 0;
    }

    void update(STGame* game) override{
        auto input = game->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)) input->requestClose();
        if(input->isKeyPressed(KEY::KEY_Q)){
            input->setCursorBound(!input->isCursorBound());
        }

        if(input->isKeyPressed(KEY::KEY_F)){
            counter++;
            game->setFullScreen(counter % 2);
        }
        m_scene->update();
    }

    void render(STGame* game) override {
        game->getGraphics()->drawScene(m_scene);
    }

    ~SampleState(){
        std::cout << "Clearing Game State" << std::endl;
        m_scene->dispose();
        delete m_scene;
    }
private:
    stUint counter;
};

int main(int argc, char** argv){
    auto inputMapping = new InputMap("Input.json");

    auto win = STGame::Init("Swing Tech", 1440, 720);
    win->setOpenGLVersion(4, 0);
    win->setTargetFPS(60);
    STGraphics::YUp = false;
    win->getInput()->setInputMap(inputMapping);
    win->addCamera(new Camera(*win, Vector3D(0.f, 0.f, -1.f), 0));
    win->addState(new SampleState(0));
    win->enterState(0);
    win->getGraphics()->enableShadow(true);
    win->getGraphics()->setRenderMode(STGraphics::DEFERRED);
    win->getGraphics()->enablePostEffect(STGraphics::BLOOM);
    win->start();

    return 0;
}