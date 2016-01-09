#include "STEntity.h"

STEntity::STEntity() {

}

void STEntity::addComponent(std::type_index type, STComponent *component) {
    m_components[type] = component;
}

void STEntity::BtSUpdate(STechWindow *window, int delta) {
    for (auto& component : m_components) {
        component.second->update(window, delta);
    }
}