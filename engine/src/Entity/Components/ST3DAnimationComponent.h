#ifndef SWINGTECH1_ST3DANIMATIONCOMPONENT_H
#define SWINGTECH1_ST3DANIMATIONCOMPONENT_H

#include "STComponent.h"
#include "STGraphicsComponent.h"
#include "../STEntity.h"

class STComponent;

class ST3DAnimationComponent : public STComponent {
public:
    explicit ST3DAnimationComponent();
    ST3DAnimationComponent(const ST3DAnimationComponent& copy);
    void init(STEntity* parent);
protected:
    STGraphicsComponent* m_gfxComponent;
};


#endif //SWINGTECH1_ST3DANIMATIONCOMPONENT_H
