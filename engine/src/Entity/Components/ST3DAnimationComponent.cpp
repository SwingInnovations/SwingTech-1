#include "ST3DAnimationComponent.h"


void ST3DAnimationComponent::init(STEntity* parent) {
    m_entity = parent;
    m_gfxComponent = m_entity->get<STGraphicsComponent>();
}

ST3DAnimationComponent::ST3DAnimationComponent() {

}

ST3DAnimationComponent::ST3DAnimationComponent(const ST3DAnimationComponent &copy) {

}
