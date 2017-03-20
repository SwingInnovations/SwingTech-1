#ifndef WAHOO_STSCRIPTCOMPONENT_H
#define WAHOO_STSCRIPTCOMPONENT_H

#include "STComponent.h"
#include "../STEntity.h"

#if __windows__
#include <sol.hpp>
#else
#include <lua5.1/sol.hpp>
#endif

class STEntity;

class STScriptComponent : public STComponent{
public:
    STScriptComponent(STEntity* entity, const std::string& fileName);
    ~STScriptComponent();

    void update();
    STEntity* m_entity;
    sol::state m_script;
private:
    STGraphicsComponent* getGraphicsComponent();
    void initScript(const std::string& fileName);
};


#endif //WAHOO_STSCRIPTCOMPONENT_H
