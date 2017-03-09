#include "STScriptComponent.h"

#include "../../STGlobal.h"

STScriptComponent::STScriptComponent(STEntity *entity, const std::string &fileName) {
    this->m_entity = entity;
    initScript(fileName);
}

STScriptComponent::~STScriptComponent() {

}

void STScriptComponent::update() {
    m_script["update"](STGame::Get());
}

void STScriptComponent::initScript(const std::string &fileName) {
    m_script.open_libraries(sol::lib::base, sol::lib::package);
    //Regsiter Commands
    m_script.set("self", m_entity);
    m_script.set("Input", Input::m_instance);
    m_script.new_usertype<Input>("Input",
                                "isKeyPressed", &Input::isKeyPressed,
                                "isKeyDown", &Input::isKeyDown);
    m_script.new_usertype<STGame>("STGame",
                                "getInput", &STGame::getInput,
                                "getTick", &STGame::getTick,
                                "getDelta", &STGame::getDelta,
                                "getWidth", &STGame::getWidth,
                                "getHeight", &STGame::getHeight);
    m_script.new_usertype<Vector2<stReal>>("Vector2", sol::constructors<sol::types<>, sol::types<stReal, stReal>>(),
                                           "setX", &Vector2<stReal>::setX,
                                           "setY", &Vector2<stReal>::setY,
                                           "getX", &Vector2<stReal>::getX,
                                           "getY", &Vector2<stReal>::getY,
                                            sol::meta_function::addition, [](Vector2<stReal> v1, Vector2<stReal> v2){
                                                                                return v1 + v2;
                                                                            },
                                            sol::meta_function::subtraction, [](Vector2<stReal> v1, Vector2<stReal> v2){
                                                                                return v1 - v2;
                                                                            },
                                            sol::meta_function::multiplication, [](Vector2<stReal> v1, Vector2<stReal> v2){
                                                                                return v1 * v2;
                                                                            },
                                            sol::meta_function::division, [](Vector2<stReal> v1, Vector2<stReal> v2){
                                                                                return v1 / v2;
                                                                            });
    m_script.new_usertype<Vector3<stReal>>("Vector3", sol::constructors<sol::types<>, sol::types<stReal, stReal, stReal>>(),
                                           "setX", &Vector3<stReal>::setX,
                                           "setY", &Vector3<stReal>::setY,
                                           "setZ", &Vector3<stReal>::setZ,
                                           "getX", &Vector3<stReal>::getX,
                                           "getY", &Vector3<stReal>::getY,
                                           "getZ", &Vector3<stReal>::getZ,
                                           "length", &Vector3<stReal>::getLength,
                                           "dot", &Vector3<stReal>::dot,
                                           "cross", &Vector3<stReal>::cross,
                                           "getInfo", &Vector3<stReal>::getInfo,
                                            sol::meta_function::addition, [](Vector3<stReal> v1, Vector3<stReal> v2){
                                                                                return v1 + v2;
                                                                            },
                                            sol::meta_function::subtraction, [](Vector3<stReal> v1, Vector3<stReal> v2){
                                                                                return v1 - v2;
                                                                            },
                                            sol::meta_function::multiplication, [](Vector3<stReal> v1, Vector3<stReal> v2){
                                                                                return v1 * v2;
                                                                            },
                                            sol::meta_function::division, [](Vector3<stReal> v1, Vector3<stReal> v2){
                                                                                return v1 / v2;
                                                                            });
    m_script.new_usertype<Vector4<stReal>>("Vector4", sol::constructors<sol::types<>, sol::types<stReal, stReal, stReal, stReal>>(),
                                           "setX", &Vector4<stReal>::setX,
                                           "setY", &Vector4<stReal>::setY,
                                           "setZ", &Vector4<stReal>::setZ,
                                           "setW", &Vector4<stReal>::setW);
    m_script.new_usertype<STEntity>("STEntity",
                                    "getTag", &STEntity::getTag,
                                    "getTransform", &STEntity::transform);
    m_script.new_usertype<Transform>("Transform", sol::constructors<sol::types<>>(),
                                     "setTranslate", sol::resolve<void(Vector3<stReal>&)>(&Transform::setTranslate),
                                     "setTranslateX", &Transform::setTranslateX,
                                     "setTranslateY", &Transform::setTranslateY,
                                     "setTranslateZ", &Transform::setTranslateZ,
                                    "getTranslate", &Transform::getTranslateF,
                                     "setRotate", sol::resolve<void(Vector3<stReal>&)>(&Transform::setRotate),
                                     "setRotateX", &Transform::setRotateX,
                                     "setRotateY", &Transform::setRotateY,
                                     "setRotateZ", &Transform::setRotateZ,
                                    "getRotate", &Transform::getRotateF,
                                     "setScale", sol::resolve<void(Vector3<stReal>&)>(&Transform::setScale),
                                    "getScale", &Transform::getScaleF);
    m_script.script_file(fileName);
}

