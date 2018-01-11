#ifndef WAHOO_STACTOR_H
#define WAHOO_STACTOR_H

#include "STEntity.h"

class STEntity;

/**
 * @brief 3D Object. Use STSpriteActor for 2D Character
 */
class STActor : public STEntity {
public:
    STActor() = default;
    STActor(const std::string& filePath);
    STActor(STMesh_Structure structure, std::string& tag, STMaterial* material);
    STActor(STMesh_Structure, std::map<std::string, std::shared_ptr<STMaterial>>);
    STActor(STEntity* parent, STMesh_Structure, std::map<std::string, STMaterial*>);
    ~STActor();

    inline void addChild_Actor(STActor* actor){
//        actor->init();
//        this->m_children.push_back((STEntity*)actor);
    }

    void AddChildActor(std::shared_ptr<STActor> actor);
    static std::shared_ptr<STActor> Create(const std::string& filename);

    void draw() override;
    void draw(STMaterial*);
    void draw(Camera*, int) override;
    void draw(STMaterial *overrideMaterial, bool flag);
};


#endif //WAHOO_STACTOR_H
