#ifndef WAHOO_STACTOR_H
#define WAHOO_STACTOR_H

#include "STEntity.h"

/*
 * Actor class describes all visible entities in the scene.
 */
class STActor : public STEntity {
public:
    STActor(const std::string& filePath, const int type, STMaterial* material);
    STActor(const std::string& filePath, STMaterial* material);
    STActor(const std::string& filePath, const int type, std::string& tag, Vector2<stInt> bounds, STMaterial* material);
    STActor(const std::string& filePath, const int type, std::string& tag, Vector2<stInt> bounds, Vector3<stInt> maxSizes, STMaterial* material);
    inline void addChild_Actor(STActor* actor){
        this->m_children.push_back((STEntity*)actor);
    }
    void draw();
    void draw(Camera*, int);
private:
    STEntity* m_parent;
};


#endif //WAHOO_STACTOR_H
