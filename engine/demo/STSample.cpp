#include "../src/Math/STCore.h"
#include "../src/Application/STGame.h"
#include "../src/Application/STSceneManager.h"
#include "../src/Application/Util/STJson.h"
#include "../src/Entity/Components/ST3DAnimationComponent.h"
#include "../src/Entity/Components/ST3DPhysicsComponent.h"
#include "../src/Application/Util/File/STFileManager.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>

class STFileManager;

/**
 * This is an example class for demonstrating How a typical game state would be setup.
 */
class SampleState : public STGameState{
public:
    SampleState(stInt id){ m_id = id; }
    void init(STGame* game) override {
        m_scene->addSkybox("green");
        game->getCamera()->setSpeed(0.025f);

        std::stringstream ss;
        cereal::BinaryOutputArchive outputArchive(ss);
        auto v1 = Vector3D(5, 6, 7);
        auto t1 = std::make_shared<Transform>();
        t1->setTranslate(Vector3D(0, 1, 2));
        t1->setRotationMode(Transform::RotationMode::Local);
        outputArchive(t1);

        cereal::BinaryInputArchive inputArchive(ss);
        auto v2 = std::make_shared<Transform>();
        inputArchive(v2);

        auto t2 = v2.get();

        auto mainLight = STLight::InitDirectionalLight(Vector3D(4.f, 5.f, 3.f), Vector3D(-.5f, -.5f, -.5f), Vector3D(0.25f, 0.25f, 0.85f));
        mainLight->get<STLightComponent>()->setTarget(Vector3D(0.f, 0.f, 0.f));

        auto accentLight = STLight::InitDirectionalLight(Vector3D(2.f, 4.f, -3.f), Vector3D(), Vector3D(1.f, 1.f, 1.f));
        accentLight->get<STLightComponent>()->setTarget(Vector3D());

        auto accentLight2 = STLight::InitDirectionalLight(Vector3D(-2.f, 4.f, -2.f), Vector3D(), Vector3D(0.f, 0.2f, 1.f));
        accentLight2->get<STLightComponent>()->setTarget(Vector3D());
        accentLight2->get<STLightComponent>()->getProperties()->intensity = 0.9f;

        std::cout << "Generated Lights" << std::endl;

        auto c2 = STActor::Create("OrbThing.fbx");
        c2->setTag("Orb");
        c2->get<STGraphicsComponent>()->getMaterial()->setMetallic(0.2f);
        c2->get<STGraphicsComponent>()->getMaterial()->setRoughness(0.1f);

//        auto diceBox = new STActor("smooth_sphere.obj");
//        diceBox->setTag("Dice");
//        diceBox->get<STGraphicsComponent>()->getMaterial()->setMetallic(0.2f);
//        diceBox->get<STGraphicsComponent>()->getMaterial()->setRoughness(0.1f);
//        //diceBox->get<STGraphicsComponent>()->getMaterial()->setDiffuseTexture("Bronze_Albedo.jpg");
//        diceBox->transform()->setTranslateX(1.0f);
//        diceBox->transform()->setTranslateY(10.f);
//        diceBox->transform()->setTranslateZ(2.f);
//        diceBox->addComponent(typeid(ST3DPhysicsComponent), new ST3DPhysicsComponent(STRigidBody::RigidBodyShape::SPHERE, {0.9f}));
//        diceBox->get<ST3DPhysicsComponent>()->setMass(10.f);
//        diceBox->get<ST3DPhysicsComponent>()->setRestitution(200.0f);
//        diceBox->get<ST3DPhysicsComponent>()->updateTransform();
//        diceBox->get<ST3DPhysicsComponent>()->toggleFreeze(true);
//        diceBox->addComponent(typeid(STScriptComponent), new STScriptComponent("dice.lua"));

        auto p = STActor::Create("plane.obj");
        p->get<STGraphicsComponent>()->getMaterial()->setDiffuseTexture("grid.png");
        p->transform()->setTranslateY(-2.f);
//        plane = new STActor("plane.obj");
//        plane->setTag("ground");
//        plane->transform()->setTranslateY(-2.f);
//        plane->get<STGraphicsComponent>()->setDiffuseTexture("grid.png");
//        plane->addComponent(typeid(ST3DPhysicsComponent), new ST3DPhysicsComponent(STRigidBody::RigidBodyShape::BOX, {5, 0.01, 5, 4}));
//        plane->get<ST3DPhysicsComponent>()->setMass(10.0f);
//        plane->get<ST3DPhysicsComponent>()->updateTransform();
//        plane->get<ST3DPhysicsComponent>()->toggleFreeze(true);
//
        m_scene->addLight(mainLight);
        m_scene->addLight(accentLight);
        m_scene->addLight(accentLight2);
//        m_scene->addActor(diceBox);
        m_scene->addActor(p);
        m_scene->addActor(c2);
//        counter = 0;
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

//		if (input->isKeyDown(KEY::KEY_L)) {
//			auto rZ = plane->transform()->getRotate().getZ();
//			plane->transform()->setRotateZ(rZ + 0.025f * game->getDelta());
//			plane->get<ST3DPhysicsComponent>()->updateTransform();
//		}
//
//		if (input->isKeyDown(KEY::KEY_J)) {
//			auto rZ = plane->transform()->getRotate().getZ();
//			plane->transform()->setRotateZ(rZ - 0.025f * game->getDelta());
//			plane->get<ST3DPhysicsComponent>()->updateTransform();
//		}
//
//        if(input->isKeyDown(KEY::KEY_I)){
//            auto rX = plane->transform()->getRotate().getX();
//            plane->transform()->setRotateX(rX + 0.025f * game->getDelta());
//            plane->get<ST3DPhysicsComponent>()->updateTransform();
//        }
//
//        if(input->isKeyDown(KEY::KEY_K)){
//            auto rX = plane->transform()->getRotate().getX();
//            plane->transform()->setRotateX(rX - 0.025f * game->getDelta());
//            plane->get<ST3DPhysicsComponent>()->updateTransform();
//        }

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