#include "../src/Math/STCore.h"
#include "../src/STGame.h"
#include "../src/STSceneManager.h"
#include "../src/Util/STJson.h"

/**
 * This is an example class for demonstrating How a typical game state would be setup.
 */
class SampleState : public STGameState{
public:
    SampleState(stInt id){ m_id = id; }
    void init(STGame* game) override {
        scene = STSceneManager::Get()->initScene(getID());
        scene->addSkybox("green");
        game->getCamera()->setSpeed(0.025f);
        Vector2<stReal> vec(5, 7);

        auto str = STJson::ToJson(vec);

        std::string errStr;
        auto copyVec = Vector2<stReal>::FromJson(str);

        auto mainLight = STLight::InitDirectionalLight(Vector3<stReal>(4.f, 5.f, 3.f), Vector3<stReal>(-.5f, -.5f, -.5f), Vector3<stReal>(0.25f, 0.25f, 0.85f));
        mainLight->get<STLightComponent>()->setTarget(Vector3<stReal>(0.f, 0.f, 0.f));

        auto accentLight = STLight::InitDirectionalLight(Vector3<stReal>(2.f, 4.f, -3.f), Vector3<stReal>(), Vector3<stReal>(1.f, 1.f, 1.f));
        accentLight->get<STLightComponent>()->setTarget(Vector3<stReal>());

        auto character = new STActor("sphere.obj");
        character->get<STGraphicsComponent>()->getMaterial()->setRoughness(0.6f);
        character->get<STGraphicsComponent>()->getMaterial()->setMetallic(0.5f);
        character->addComponent(typeid(STScriptComponent), new STScriptComponent("Suzanne_Control.lua"));
        character->setAttribute("speedFactor", 0.025f);
        character->transform()->setRotateX(-90);
        character->transform()->setRotationMode(Transform::Local);

        auto characterTransform = character->transform()->to_json().dump();
        auto newTransform = Transform::FromJson(characterTransform);

        auto plane = new STActor("plane.obj");
        plane->transform()->setTranslateY(-1.f);
        plane->get<STGraphicsComponent>()->setDiffuseTexture("grid.png");
        plane->get<STGraphicsComponent>()->getMaterial()->setRoughness(0.4);

        scene->addLight(mainLight);
        scene->addLight(accentLight);
        scene->addActor(character);
        scene->addActor(plane);
    }

    void update(STGame* game, stUint delta) override {
        auto input = game->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)) input->requestClose();
        if(input->isKeyPressed(KEY::KEY_Q)){
            input->setCursorBound(!input->isCursorBound());
        }
        scene->update();
    }

    void render(STGame* game) override {
        game->getGraphics()->drawScene(scene);
    }

    ~SampleState(){
        delete scene;
    }

private:
    STScene* scene;
};

int main(int argc, char** argv){
    auto inputMapping = new InputMap("Input.json");
//    inputMapping->addMapping(MOVEMENT::FORWARD, KEY::KEY_W);
//    inputMapping->addMapping(MOVEMENT::BACKWARD, KEY::KEY_S);
//    inputMapping->addMapping(MOVEMENT::STRAFE_LEFT, KEY::KEY_A);
//    inputMapping->addMapping(MOVEMENT::STRAFE_RIGHT, KEY::KEY_D);

    auto win = STGame::Init("Swing Tech", 1440, 720);
    win->setOpenGLVersion(4, 0);
    win->setTargetFPS(60);
    win->setClearColor(0.0f, 0.0f, 0.67f, 1.0f);
    STGraphics::YUp = false;
    win->getInput()->setInputMap(inputMapping);
    win->addCamera(new Camera(*win, Vector3<stReal>(0.f, 0.f, -1.f), 0));
    win->addState(new SampleState(0));
    win->enterState(0);
    win->getGraphics()->enableShadow(true);
    win->getGraphics()->setRenderMode(STGraphics::DEFERRED);
    win->start();
}