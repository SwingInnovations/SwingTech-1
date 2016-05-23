#ifndef WAHOO_STSCRIPTCOMPONENT_H
#define WAHOO_STSCRIPTCOMPONENT_H

#include <iostream>

#include "../ext/LuaBridge.h"

extern "C"{
    #include "../ext/lualib.h"
    #include "../ext/lauxlib.h"
    #include "../ext/lua.h"

};

#include "STComponent.h"
#include "STEntity.h"

using namespace luabridge;

class STEntity;

class STScriptComponent : public STComponent{
public:
    STScriptComponent(STEntity* entity, const std::string& fileName);
    ~STScriptComponent();

    void update(STEntity* entity, STGame* game, int delta);

    void test();
    static int l_test(lua_State*);
private:
    STEntity* entity;
};


#endif //WAHOO_STSCRIPTCOMPONENT_H
