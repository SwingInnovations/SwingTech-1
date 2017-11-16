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
        Vector2<stReal> vec(5, 7);

        auto str = STJson::ToJson(vec);

        std::string errStr;
        auto copyVec = Vector2<stReal>::FromJson(str);

        auto mainLight = STLight::InitDirectionalLight(Vector3<stReal>(4.f, 5.f, 3.f), Vector3<stReal>(-.5f, -.5f, -.5f), Vector3<stReal>(0.25f, 0.25f, 0.85f));
        mainLight->get<STLightComponent>()->setTarget(Vector3<stReal>(0.f, 0.f, 0.f));

        auto accentLight = STLight::InitDirectionalLight(Vector3<stReal>(2.f, 4.f, -3.f), Vector3<stReal>(), Vector3<stReal>(1.f, 1.f, 1.f));
        accentLight->get<STLightComponent>()->setTarget(Vector3<stReal>());

        auto character = new STActor("smooth_sphere.obj");
        character->get<STGraphicsComponent>()->getMaterial()->setRoughness("Bronze_Roughness.jpg");
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
        m_scene->addLight(mainLight);
        m_scene->addLight(accentLight);
        m_scene->addActor(character);
        m_scene->addActor(plane);
        counter = 0;
    }

    void update(STGame* game) override{
        auto input = game->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)) input->requestClose();
        if(input->isKeyPressed(KEY::KEY_Q)){
            input->setCursorBound(!input->isCursorBound());
        }
        if(input->isKeyPressed(KEY::KEY_L)){
            this->m_scene->sendMessage("onPress");
        }

        if(input->isKeyPressed(KEY::KEY_F)){
            counter++;
            game->setFullScreen(counter % 3);
        }
        m_scene->update();
    }

    void render(STGame* game) override {
        game->getGraphics()->drawScene(m_scene);
    }

    ~SampleState(){
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
    win->addCamera(new Camera(*win, Vector3<stReal>(0.f, 0.f, -1.f), 0));
    win->addState(new SampleState(0));
    win->enterState(0);
    win->getGraphics()->enableShadow(true);
    win->getGraphics()->setRenderMode(STGraphics::DEFERRED);
    win->getGraphics()->enablePostEffect(STGraphics::BLOOM);
    win->start();
}