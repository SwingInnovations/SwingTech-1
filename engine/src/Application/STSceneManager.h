#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include <map>
#include "../Entity/STEntity.h"
#include "../Entity/STActor.h"
#include "../Entity/STLight.h"
#include "../Entity/STCamera.h"
#include "../Math/Shape/BoundingBox.h"
#include "Util/Data_Structure/STQueue.h"

class STRenderScene;
class STLight;
class STInterWidget;

class OctNode{
public:
    explicit OctNode(STBoundingBox* boundingBox);

    explicit OctNode(const OctNode& copy);

    OctNode(Vector3<stReal>& originPt, Vector3<stReal>& extants);

    OctNode(STEntity* data, STBoundingBox* boundingBox);

    ~OctNode();

    void insert(STEntity* newEntity);

    int getOctantContainingPt(const Vector3<stReal>& point);

    bool isLeafNode()const;

    void update();

private:
    STEntity* data;
    STBoundingBox* boundingBox;
    OctNode* parent;
    OctNode* children[8];
};

/**
 * Handles 2D scenes.
 */
class QuadNode{
private:
    QuadNode* children[4];
};

class STScene{
public:
    STScene();

    explicit STScene(stUint index);

    static void RemoveEntity(STEntity* entity);
    static void RemoveEntityQueue(STEntity* entity);

    void setRenderScene(STRenderScene* renderScene);
    STRenderScene* getRenderScene(){ return m_renderScene; }

    ~STScene();

    void addCamera(std::shared_ptr<STCamera> newCamera);

    /**
     * Adds Actor to scene.
     * @param actor
     */
    void addActor(std::shared_ptr<STActor> actor);

    /**
     * Adds Light to the scene
     * @param light
     */
    void addLight(std::shared_ptr<STLight> light);

    void addUIElement(STInterWidget* ui);

    void update();
    void dispose();

    /**
     * Sends a message to all Actors.
     * @param msg
     */
    void sendMessage(const std::string &msg);

    /**
     * Sets the skybox using the default skybox shader.
     * @param filePath
     */
    void addSkybox(const std::string& filePath);

    /**
     * Sets the skybox using an override shader.
     * @param file
     * @param shader
     */
    inline void addSkybox(const std::string& file, const std::string& shader);

    const std::vector<std::shared_ptr<STActor>> &getActors()const{ return actors; }
    const std::vector<std::shared_ptr<STLight>> &getLights()const{ return lights; }
    const std::vector<STInterWidget*> &getUIElements()const{ return uiElements; }

    STCamera*  getActiveCamera()const;

    const std::string& getSkyboxName()const{ return skyboxName; }
    const std::string& getSkyboxShader()const{ return skyboxShader; }

    const stUint getIndex()const{ return m_index; }
    const stUint getShadowCount()const{ return m_numShadows; }

    void save(std::ofstream& out);
    void load(std::ifstream& in);
private:
    stUint m_index;
    stUint m_numShadows;
    STQueue<STEntity*> pendingEntities;
    OctNode* rootNode;
    std::vector<std::shared_ptr<STActor>> actors;
    std::vector<std::shared_ptr<STLight>> lights;
    std::vector<STInterWidget*> uiElements;
    std::vector<STEntity*> removeQueue;
    std::string skyboxName;
    std::string skyboxShader;
    STRenderScene* m_renderScene;
    std::vector<std::shared_ptr<STCamera>> m_cameras;
    stUint m_activeCameraIndex;
};

#endif //WAHOO_STSCENEMANAGER_H
