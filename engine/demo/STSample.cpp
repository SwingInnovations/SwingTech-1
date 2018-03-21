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
        m_scene->getActiveCamera()->get<STCameraComponent>()->setSpeed(0.025f);
        m_scene->getActiveCamera()->transform()->setTranslate(Vector3D(0.f, 0.f, 0.f));

        auto mainLight = STLight::InitDirectionalLight(Vector3D(4.f, 5.f, 3.f), Vector3D(-.5f, -.5f, -.5f), Vector3D(0.25f, 0.25f, 0.85f));
        mainLight->get<STLightComponent>()->setTarget(Vector3D(0.f, 0.f, 0.f));

        auto accentLight = STLight::InitDirectionalLight(Vector3D(2.f, 4.f, -3.f), Vector3D(), Vector3D(1.f, 1.f, 1.f));
        accentLight->get<STLightComponent>()->setTarget(Vector3D());

        auto accentLight2 = STLight::InitDirectionalLight(Vector3D(-2.f, 4.f, -2.f), Vector3D(), Vector3D(0.f, 0.2f, 1.f));
        accentLight2->get<STLightComponent>()->setTarget(Vector3D());
        accentLight2->get<STLightComponent>()->getProperties()->intensity = 0.9f;

        auto s = STActor::Create("OrbThing.fbx");
        s->transform()->setTranslate({0.f, 5.f, 0.f});
		s->get<STRendererComponent>()->GetMaterial()->setDiffuseColor(STColor(1.0, 0.8, 0.0, 1.0));
        auto physHandle = s->addComponent<ST3DPhysicsComponent>(new ST3DPhysicsComponent(STRigidBody::CAPSULE_Y, {0.9f, 2.0f}));
        physHandle->updateTransform();
        s->addScript("Control.lua");
//
//        STFileManager::Write("testEntity.bin", s);

//        sphere = STFileManager::Read<STActor>("testEntity.bin");
//        sphere->setName("Sphere");
//        sphere->get<ST3DPhysicsComponent>()->updateTransform();
//        sphere->get<ST3DPhysicsComponent>()->setMass(30.f);
//        sphere->get<ST3DPhysicsComponent>()->setRestitution(0.5f);
//        sphere->get<STEventComponent>()->addEvent("onCollision", [](STEntity* self, STEntity* other){
//            if(other != nullptr){
//                auto gfx = self->get<STRendererComponent>();
//                gfx->getMaterial()->setDiffuseColor(Vector4D(1.f, 0.f, 1.f, 1.f));
//                gfx->getMaterial()->setMetallic(0.2f);
//                gfx->getMaterial()->setRoughness(0.f);
//            }
//        });

        auto s2 = STFileManager::Read<STActor>("testEntity.bin");
        s2->setName("Sphere2");
        s2->transform()->setTranslate({3.5f, 5, 3.5f});
        s2->get<ST3DPhysicsComponent>()->updateTransform();
        s2->get<ST3DPhysicsComponent>()->setRestitution(0.5f);
        //s2->addScript("SphereScript.lua");
        sphere2 = s2;

        auto l = STFileManager::Read<STLight>("testLight");
        l->transform()->setTranslate({2.f, 10.f, 2.f});
		light = l;

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
        m_scene->addActor(s);
    }

    void update(STGame* game) override{
        auto input = game->getInput();
		auto delta = game->getDelta();
        if(input->isKeyPressed(KEY::KEY_ESC)) input->requestClose();
        if(input->isKeyPressed(KEY::KEY_Q)){
            input->setCursorBound(!input->isCursorBound());
            input->setCursorVisible(!input->isCursorBound());
        }

        if(input->isKeyPressed(KEY::KEY_F)) {
            counter++;
            game->setFullScreen(counter % 2);
        }

        auto sphere2Handle = sphere2.get();

        if(input->isMousePressed(1)){
            auto newSphere = STActor::Create("smooth_sphere.obj");
            stReal nX =(rand() % 6) - 3.f, nZ = (rand() % 6) - 3.f;
            auto s = (stReal)(rand() % 3);
            newSphere->transform()->setScale({s, s, s});
            newSphere->transform()->setTranslate({nX, 5.f, nZ});
            auto p = newSphere->addComponent<ST3DPhysicsComponent>(new ST3DPhysicsComponent(STRigidBody::SPHERE, {s}));
            p->updateTransform();
            p->setMass(10.f);
            newSphere->addScript("SphereScript.lua");
            m_scene->addActor(newSphere);
        }

		if (input->isKeyDown(KEY::KEY_B)) { 
			auto oldPos = light->transform()->getTranslate().getX();
			oldPos += 0.025f * delta;
			light->transform()->setTranslateX(oldPos);
		}

		if (input->isKeyDown(KEY::KEY_N)) {
			auto oldPos = light->transform()->getTranslate().getX();
			oldPos -= 0.025f * delta;
			light->transform()->setTranslateX(oldPos);
		}

        if(input->isKeyPressed(KEY::KEY_E)){
            if(sphere){
                STScene::RemoveEntity(sphere.get());
            }
        }
        m_scene->update();
    }

    void render(STGame* game) override {
        game->getGraphics()->drawScene(m_scene);
    }

    ~SampleState()override{
        std::cout << "Clearing Game State" << std::endl;
        //STFileManager::Write("testScene.bin", m_scene);
        m_scene->dispose();
        delete m_scene;
    }

private:
    stUint counter;
    std::shared_ptr<STActor> sphere;
    std::shared_ptr<STActor> sphere2;
	std::shared_ptr<STLight> light;
};

#if _MSC_VER > 1900
    //For use with MSVC Compiler
    int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow){
#else
	int main(int argc, char** argv){ 
#endif
		auto inputMapping = new InputMap("Input.json");

		STRenderInfo renderInfo;
		renderInfo.renderer = STRenderInfo::OPENGL;
		renderInfo.maxVersion = 4;
		renderInfo.minVersion = 0;

        auto win = STGame::Init("Swing Tech", 1440, 720, renderInfo, STPhysics::PhysicsEngine::BULLET);
        win->setTargetFPS(60);
        STGraphics::YUp = false;
        win->getInput()->setInputMap(inputMapping);
        win->addState(new SampleState(0));
        win->enterState(0);
        win->getGraphics()->enableShadow(true);
		win->getGraphics()->setShadowResolution(768);
        win->getGraphics()->setRenderMode(STGraphics::DEFERRED);
        win->getGraphics()->enablePostEffect(STGraphics::BLOOM | STGraphics::MOTION_BLUR);
        win->start();

        return 0;
    }

