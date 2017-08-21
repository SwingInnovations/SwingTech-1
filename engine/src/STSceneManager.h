#ifndef WAHOO_STSCENEMANAGER_H
#define WAHOO_STSCENEMANAGER_H

#include <vector>
#include <map>
#include "Entity/STEntity.h"
#include "Entity/STActor.h"
#include "Entity/STLight.h"
#include "Math/Shape/BoundingBox.h"
#include "Util/Data_Structure/STQueue.h"

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

class STScene{
public:
    STScene();

    STScene(stUint index);

    ~STScene();

    void addActor(STActor* actor);

    void addLight(STLight* light);

    void addUIElement(STInterWidget* ui);

    void update();

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

    const std::vector<STActor*> &getActors()const{ return actors; }
    const std::vector<STLight*> &getLights()const{ return lights; }
    const std::vector<STInterWidget*> &getUIElements()const{ return uiElements; }

    const std::string& getSkyboxName()const{ return skyboxName; }
    const std::string& getSkyboxShader()const{ return skyboxShader; }

    const stUint getIndex()const{ return m_index; }
    const stUint getShadowCount()const{ return m_numShadows; }

private:
    stUint m_index;
    stUint m_numShadows;
    STQueue<STEntity*> pendingEntities;
    OctNode* rootNode;
    std::vector<STActor*> actors;
    std::vector<STLight*> lights;
    std::vector<STInterWidget*> uiElements;
    std::string skyboxName;
    std::string skyboxShader;
};

class STSceneManager{
public:
    static STSceneManager* m_Instance;

    static STSceneManager* Get(){
        if(m_Instance == nullptr) m_Instance = new STSceneManager;
        return m_Instance;
    }

    STSceneManager() = default;

    inline STScene* initScene(const stUint index){
        scenes.insert(std::pair<stUint, STScene*>(index, new STScene(index)));
        //Allocate something to manage the scene
        auto grphx = STGame::Get()->getGraphics();
        grphx->initScene(index);
        return scenes[index];
    }

    inline STScene* getScene(stUint index){
        if(index < scenes.size()){
            return scenes[index];
        }
    }

private:
    std::map<stUint, STScene*> scenes;
};

#endif //WAHOO_STSCENEMANAGER_H
