#ifndef WAHOO_STSCRIPTCOMPONENT_H
#define WAHOO_STSCRIPTCOMPONENT_H

#include <iostream>

#include "LuaBridge.h"

extern "C"{
    #include "lualib.h"
    #include "lauxlib.h"
    #include "lua.h"
};

#include "STComponent.h"
#include "../STEntity.h"

#define ADD_FUNC(x) addFunction(#x, &STScriptComponent::x)

using namespace luabridge;

class STEntity;

class STScriptComponent : public STComponent{
public:
    STScriptComponent(STEntity* entity, const std::string& fileName);
    ~STScriptComponent();

    void update(STEntity* entity, STGame* game, int delta);
    void update(STEntity* entity, STGame* game);
    void test();
    void test2();
    static int l_test(lua_State*);
private:
    template<typename T, typename R, typename  S>
    void initFunctions(lua_State* L);
    STEntity*m_entity;
};


#endif //WAHOO_STSCRIPTCOMPONENT_H
