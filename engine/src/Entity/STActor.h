#ifndef WAHOO_STACTOR_H
#define WAHOO_STACTOR_H

#include "STEntity.h"

/*
 * Actor class describes all visible entities in the scene.
 */
class STActor : public STEntity {
public:
    STActor(const std::string& filePath, const int type, STMaterial* material);
    void draw();
private:
    STEntity* m_parent;
};


#endif //WAHOO_STACTOR_H
