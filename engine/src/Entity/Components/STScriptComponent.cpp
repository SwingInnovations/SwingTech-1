#include "STScriptComponent.h"

#include "../../STGlobal.h"

STScriptComponent::STScriptComponent(STEntity *entity, const std::string &fileName) {
    this->m_entity = entity;
    m_script.open_libraries(sol::lib::base, sol::lib::package);
    m_script.script_file(fileName);
}

STScriptComponent::~STScriptComponent() {

}

void STScriptComponent::update() {
    m_script["update"]();
}

