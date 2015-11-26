#include "STEntity.h"

STEntity::STEntity() {

}

void STEntity::addComponent(std::type_index type, STComponent *component) {
    m_componenets[type] = component;
}