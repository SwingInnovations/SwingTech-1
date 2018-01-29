#include "STComponent.h"

std::shared_ptr<STComponentObjectFactory> STComponentObjectFactory::Instance = nullptr;

void STComponent::init(std::shared_ptr<STEntity> &newParent) {
    this->m_entity = newParent;
}
