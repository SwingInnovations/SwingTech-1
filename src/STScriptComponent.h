#ifndef WAHOO_STSCRIPTCOMPONENT_H
#define WAHOO_STSCRIPTCOMPONENT_H

#include <iostream>

#include "../ext/lualib.h"
#include "../ext/lauxlib.h"
#include "../ext/lua.h"

#include "STComponent.h"
#include "STEntity.h"

class STEntity;

class STScriptComponent : public STComponent{
public:
    STScriptComponent(STEntity* entity, const std::string& fileName);
    ~STScriptComponent();
    void test();
    static int l_test(lua_State*);
private:
    STEntity* entity;
};


#endif //WAHOO_STSCRIPTCOMPONENT_H
