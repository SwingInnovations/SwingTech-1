#include "STScriptComponent.h"

STScriptComponent::STScriptComponent(STEntity *entity, const std::string &fileName) {
    this->entity = entity;
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if(luaL_loadfile(L, fileName.c_str())){
        std::cout << "Failed to load file!" << std::endl;
    }
    lua_pushcfunction(L, l_test);
    lua_setglobal(L, "test");
    lua_pcall(L, 0, 0,0);

    lua_close(L);

}

STScriptComponent::~STScriptComponent() {

}

void STScriptComponent::test() {
    std::cout << "Test! " << std::endl;
}


int STScriptComponent::l_test(lua_State *state) {
    const char* str = lua_tostring(state, 1);
    std::cout << str << std::endl;
    return 0;
}

void STScriptComponent::update(STEntity *entity, STGame *game, int delta) {

}
