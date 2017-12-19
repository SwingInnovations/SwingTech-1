#include "../src/Math/STCore.h"
#include "../src/Application/STGame.h"
#include "../src/Application/STSceneManager.h"
#include "../src/Application/Util/STJson.h"
#include "../src/Entity/Components/ST3DAnimationComponent.h"
#include "../src/Entity/Components/ST3DPhysicsComponent.h"

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

        auto accentLight2 = STLight::InitDirectionalLight(Vector3D(-2.f, 4.f, -2.f), Vector3D(), Vector3D(0.f, 0.2f, 1.f));
        accentLight2->get<STLightComponent>()->setTarget(Vector3D());
        accentLight2->get<STLightComponent>()->getProperties()->intensity = 0.9f;

//        auto character = new STActor("humanoid.fbx");
//        character->setTag("Main");
//        character->get<STGraphicsComponent>()->getMaterial()->setMetallic(0.1f);
//        character->addComponent(typeid(STScriptComponent), new STScriptComponent("Suzanne_Control.lua"));
//        character->setAttribute("speedFactor", 0.025f);
//        character->transform()->setRotationMode(Transform::Local);
//
//        auto c2 = new STActor("animCylinder.fbx");
//        c2->transform()->setTranslateX(4.f);
//        c2->transform()->setTranslateZ(4.f);
//        c2->transform()->setRotationMode(Transform::Local);
//        c2->get<STGraphicsComponent>()->getMaterial()->setDiffuseColor(STColor(GREEN));

        auto diceBox = new STActor("smooth_sphere.obj");
        diceBox->setTag("Dice");
        diceBox->addComponent(typeid(STScriptComponent), new STScriptComponent("dice.lua"));
        diceBox->get<STGraphicsComponent>()->getMaterial()->setMetallic(0.2f);
        diceBox->get<STGraphicsComponent>()->getMaterial()->setRoughness(0.1f);
        diceBox->get<STGraphicsComponent>()->getMaterial()->setDiffuseTexture("Bronze_Albedo.jpg");
        diceBox->transform()->setTranslateX(1.0f);
        diceBox->transform()->setTranslateY(10.f);
        diceBox->transform()->setTranslateZ(2.f);
        diceBox->addComponent(typeid(ST3DPhysicsComponent), new ST3DPhysicsComponent(STRigidBody::RigidBodyShape::SPHERE, {1.f}));
        diceBox->get<ST3DPhysicsComponent>()->setMass(100.f);
        diceBox->get<ST3DPhysicsComponent>()->setRestitution(50.0f);
        diceBox->get<ST3DPhysicsComponent>()->updateTransform();
        diceBox->get<ST3DPhysicsComponent>()->toggleFreeze(true);

        auto plane = new STActor("plane.obj");
        plane->setTag("ground");
        plane->transform()->setTranslateY(-2.f);
        plane->get<STGraphicsComponent>()->setDiffuseTexture("grid.png");
        plane->addComponent(typeid(ST3DPhysicsComponent), new ST3DPhysicsComponent(STRigidBody::RigidBodyShape::BOX, {20, 0.01, 20, 4}));
        plane->get<ST3DPhysicsComponent>()->setMass(10.0f);
        plane->get<ST3DPhysicsComponent>()->updateTransform();
        plane->get<ST3DPhysicsComponent>()->toggleFreeze(true);

        m_scene->addLight(mainLight);
        m_scene->addLight(accentLight);
        m_scene->addLight(accentLight2);
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

        if(input->isKeyPressed(KEY::KEY_Y)){
            for(auto actor : m_scene->getActors()){
                if(actor->getTag() == "Dice"){
                    actor->get<ST3DPhysicsComponent>()->toggleFreeze(false);
                    actor->get<ST3DPhysicsComponent>()->applyForce(Vector3D(0, -20, 0));
                    actor->get<ST3DPhysicsComponent>()->applyGravity();
                }
            }
        }

        if(input->isKeyPressed(KEY::KEY_R)){
            for(auto actor : m_scene->getActors()){
                if(actor->getTag() == "Dice"){
                    actor->transform()->setTranslateY(10.f);
                    actor->get<ST3DPhysicsComponent>()->updateTransform();
                    actor->get<ST3DPhysicsComponent>()->setActive(true);
                    actor->get<ST3DPhysicsComponent>()->applyForce(Vector3D(0, -20, 0));
                    actor->get<ST3DPhysicsComponent>()->applyGravity();
                }
            }
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

    auto win = STGame::Init("Swing Tech", 1440, 720, STPhysics::PhysicsEngine::BULLET);
    win->setOpenGLVersion(4, 0);
    win->setTargetFPS(60);
    STGraphics::YUp = false;
    win->getInput()->setInputMap(inputMapping);
    win->addCamera(new Camera(*win, Vector3D(0.f, 1.f, -1.f), 0));
    win->addState(new SampleState(0));
    win->enterState(0);
    win->getGraphics()->enableShadow(true);
    win->getGraphics()->setRenderMode(STGraphics::DEFERRED);
    win->start();

    return 0;
}