#include "STScriptComponent.h"

#include "../../STGlobal.h"

STScriptComponent::STScriptComponent(STEntity *entity, const std::string &fileName) {
    this->m_entity = entity;
//    lua_State* L = luaL_newstate();
//    luaL_openlibs(L);
//    if(luaL_loadfile(L, fileName.c_str())){
//        std::cout << "Failed to load file!" << std::endl;
//    }
//    initFunctions<stReal, stReal, stReal>(L);
//    lua_pushcfunction(L, l_test);
//    lua_setglobal(L, "test");
//    lua_pcall(L, 0, 0,0);
//
//    lua_close(L);

}

STScriptComponent::~STScriptComponent() {

}

//void STScriptComponent::test() {
//    std::cout << "Test! " << std::endl;
//}
//
//
//int STScriptComponent::l_test(lua_State *state) {
//    const char* str = lua_tostring(state, 1);
//    std::cout << str << std::endl;
//    return 0;
//}
//
//
//template<typename T, typename R, typename  S>
//void STScriptComponent::initFunctions(lua_State *L) {
//    getGlobalNamespace(L)
//            .beginClass<STScriptComponent>("STScriptComponent")
//            .ADD_FUNC(test)
//            .ADD_FUNC(test2)
//            .endClass()
//            .beginClass<Vector2<T>>("Vector2")
//            .addFunction("setX", &Vector2<T>::setX)
//            .addFunction("setY", &Vector2<T>::setY)
//            .addFunction("getX", &Vector2<T>::getX)
//            .addFunction("getY", &Vector2<T>::getY)
//            .endClass();
//}
//
//void STScriptComponent::test2() {
//    std::cout << "This is another test!" << std::endl;
//}

void STScriptComponent::update() {

}

