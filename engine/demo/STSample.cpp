#include "../src/Math/STCore.h"
#include "../src/Application/STGame.h"
#include "../src/Application/STSceneManager.h"
#include "../src/Application/Util/STJson.h"
#include "../src/Entity/Components/ST3DAnimationComponent.h"
#include "../src/Entity/Components/ST3DPhysicsComponent.h"
#include "../src/Application/Util/File/STFileManager.h"
#include "../src/Entity/Components/STEventComponent.h"

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

        auto mainLight = STLight::InitDirectionalLight(Vector3D(4.f, 5.f, 3.f), Vector3D(-.5f, -.5f, -.5f), Vector3D(0.25f, 0.25f, 0.85f));
        mainLight->get<STLightComponent>()->setTarget(Vector3D(0.f, 0.f, 0.f));

        auto accentLight = STLight::InitDirectionalLight(Vector3D(2.f, 4.f, -3.f), Vector3D(), Vector3D(1.f, 1.f, 1.f));
        accentLight->get<STLightComponent>()->setTarget(Vector3D());

        auto accentLight2 = STLight::InitDirectionalLight(Vector3D(-2.f, 4.f, -2.f), Vector3D(), Vector3D(0.f, 0.2f, 1.f));
        accentLight2->get<STLightComponent>()->setTarget(Vector3D());
        accentLight2->get<STLightComponent>()->getProperties()->intensity = 0.9f;

//        auto s = STActor::Create("smooth_sphere.obj");
//        s->transform()->setTranslate({0.f, 5.f, 0.f});
//        auto physHandle = s->addComponent<ST3DPhysicsComponent>(new ST3DPhysicsComponent(STRigidBody::SPHERE, {0.9f}));
//        physHandle->updateTransform();
//
//        STFileManager::Write("testEntity.bin", s);

        auto sphere = STFileManager::Read<STActor>("testEntity.bin");
        sphere->setName("Sphere");
        sphere->get<ST3DPhysicsComponent>()->updateTransform();
        sphere->get<ST3DPhysicsComponent>()->setMass(30.f);
        sphere->get<ST3DPhysicsComponent>()->setRestitution(0.5f);
        sphere->get<STEventComponent>()->addEvent("onCollision", [](STEntity* self, STEntity* other){
            if(other != nullptr){
                auto gfx = self->get<STRendererComponent>();
                gfx->getMaterial()->setDiffuseColor(Vector4D(1.f, 0.f, 0.f, 1.f));
                gfx->getMaterial()->setMetallic(0.2f);
                gfx->getMaterial()->setRoughness(0.f);
            }
        });

        STFileManager::Write("testLight", accentLight2);

        auto l = STFileManager::Read<STLight>("testLight");

        auto p = STActor::Create("plane.obj");
        p->setName("Plane");
        p->get<STRendererComponent>()->getMaterial()->setDiffuseTexture("grid.png");
        p->transform()->setTranslateY(-2.f);
        auto pHandle = p->addComponent<ST3DPhysicsComponent>(new ST3DPhysicsComponent(STRigidBody::RigidBodyShape::BOX, {4.f, 0.1f, 4.f}));
        pHandle->toggleFreeze(true);
        pHandle->updateTransform();

        m_scene->addLight(mainLight);
        m_scene->addLight(accentLight);
        m_scene->addLight(l);
        m_scene->addActor(p);
        m_scene->addActor(sphere);
    }

    void update(STGame* game) override{
        auto input = game->getInput();
        if(input->isKeyPressed(KEY::KEY_ESC)) input->requestClose();
        if(input->isKeyPressed(KEY::KEY_Q)){
            input->setCursorBound(!input->isCursorBound());
            input->setCursorVisible(!input->isCursorBound());
        }

        if(input->isKeyPressed(KEY::KEY_F)){
            counter++;
            game->setFullScreen(counter % 2);
        }

        if(input->isMousePressed(1)){
            auto pos = game->getCamera()->transform()->getTranslate();
            auto forward = game->getCamera()->getForward();
            auto end = forward * 5.f;

            auto newSphere = STActor::Create("smooth_sphere.obj");
            auto nX = (rand() % 6) - 3.f;
            auto nZ = (rand() % 6) - 3.f;

            auto s = (stReal)(rand() % 3);
            newSphere->transform()->setScale({s, s, s});

            newSphere->transform()->setTranslate({nX, 5.f, nZ});
            newSphere->addAttribute("hasChanged", 0);
            newSphere->get<STEventComponent>()->addEvent("onCollision", [](STEntity* self, STEntity* other){
                if(self->getAttributei("hasChanged") == 0){
                    self->setAttribute("hasChanged", 1);
                    auto r = (rand() % 100) / 100.f;
                    auto g = (rand() % 100) / 100.f;
                    auto b = (rand() % 100) / 100.f;
                    self->get<STRendererComponent>()->getMaterial()->setDiffuseColor(Vector4D(r, g, b, 1.f));
                }
            });
            auto p = newSphere->addComponent<ST3DPhysicsComponent>(new ST3DPhysicsComponent(STRigidBody::SPHERE, {s}));
            p->updateTransform();
            p->setMass(50.0f);
            p->setRestitution(0.5f);

            m_scene->addActor(newSphere);
        }

        m_scene->update();
    }

    void render(STGame* game) override {
        game->getGraphics()->drawScene(m_scene);
    }

    ~SampleState()override{
        std::cout << "Clearing Game State" << std::endl;
        STFileManager::Write("testScene.bin", m_scene);
        m_scene->dispose();
        delete m_scene;
    }

private:
    stUint counter;
    std::shared_ptr<STEntity> sphere;
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