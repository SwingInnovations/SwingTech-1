#ifndef WAHOO_STACTOR_H
#define WAHOO_STACTOR_H

#include "STEntity.h"

class STEntity;

/*
 * Actor class describes all visible entities in the scene.
 */
class STActor : public STEntity {
public:
    STActor(const std::string& filePath, STMaterial* material);
    STActor(const std::string& filePath);
    STActor(STMesh_Structure structure, std::string& tag, STMaterial* material);
    STActor(STMesh_Structure, std::map<std::string, STMaterial*>);
    STActor(STEntity* parent, STMesh_Structure, std::map<std::string, STMaterial*>);
    ~STActor();
    inline void addChild_Actor(STActor* actor){
        this->m_children.push_back((STEntity*)actor);
    }
    void draw() override;
    void draw(STMaterial*);
    void draw(Camera*, int);
    void draw(STMaterial *overrideMaterial, bool flag);
private:
    STEntity* m_parent;


};


#endif //WAHOO_STACTOR_H
