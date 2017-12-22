#include "STScriptComponent.h"

#include "../../Graphics/Camera.h"
#include "STEventComponent.h"

STScriptComponent::STScriptComponent(STEntity *entity, const std::string &fileName) {
    initScript(fileName);
}

STScriptComponent::STScriptComponent(const std::string &fileName) {
    this->scriptName = fileName;
}

STScriptComponent::~STScriptComponent() {

}

void STScriptComponent::update() {
    m_script["update"](m_entity);
}

void STScriptComponent::initScript(const std::string &fileName) {
    m_script.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
    //Regsiter Commands
    m_script.set_function("getGraphicsComponent",[](STEntity* ent){return ent->get<STGraphicsComponent>();});
    m_script.set_function("getEventComponent", [](STEntity* ent){ return ent->get<STEventComponent>(); });
    m_script.set_function("addEvent", [](STEntity* ent, const std::string& name){
        ent->get<STScriptComponent>()->registerEvent(ent, name);
    });
    m_script.new_usertype<Input>("Input",
                                "isKeyPressed", &Input::isKeyPressed,
                                "isKeyDown", &Input::isKeyDown,
                                "setCursorBound", &Input::setCursorBound,
                                "setCursorVisible", &Input::setCursorVisible,
                                "isCursorBound", &Input::isCursorBound);
    m_script.new_usertype<Camera>("Camera",
                                "getForward", &Camera::getForward,
                                "getUp", &Camera::getUp);
    m_script.new_enum("RotationMode",
                "Global", 0,
                "Local", 1);
    m_script.new_enum("KEY",
               "KEY_A", KEY::KEY_A,
                "KEY_B", KEY::KEY_B,
                "KEY_C", KEY::KEY_C,
                "KEY_D", KEY::KEY_D,
                "KEY_E", KEY::KEY_E,
                "KEY_F", KEY::KEY_F,
                "KEY_G", KEY::KEY_G,
                "KEY_H", KEY::KEY_H,
                "KEY_I", KEY::KEY_I,
                "KEY_J", KEY::KEY_J,
                "KEY_K", KEY::KEY_K,
                "KEY_L", KEY::KEY_L,
                "KEY_M", KEY::KEY_M,
                "KEY_N", KEY::KEY_N,
                "KEY_O", KEY::KEY_O,
                "KEY_P", KEY::KEY_P,
                "KEY_Q", KEY::KEY_Q,
                "KEY_R", KEY::KEY_R,
                "KEY_S", KEY::KEY_S,
                "KEY_T", KEY::KEY_T,
                "KEY_U", KEY::KEY_U,
                "KEY_V", KEY::KEY_V,
                "KEY_W", KEY::KEY_W,
                "KEY_X", KEY::KEY_X,
                "KEY_Y", KEY::KEY_Y,
                "KEY_Z", KEY::KEY_Z);
    m_script.new_enum("JOYSTICK_AXIS",
                "X_AXIS", JOYSTICK_AXIS::X_AXIS,
                "Y_AXIS", JOYSTICK_AXIS::Y_AXIS,
                "Z_AXIS", JOYSTICK_AXIS::Z_AXIS);
    m_script.new_enum("JOYSTICK_BUTTON",
                "BUTTON_1", JOYSTICK_BUTTON::BUTTON_1,
                "BUTTON_2", JOYSTICK_BUTTON::BUTTON_2,
                "BUTTON_3", JOYSTICK_BUTTON::BUTTON_3,
                "BUTTON_4", JOYSTICK_BUTTON::BUTTON_4,
                "BUTTON_5", JOYSTICK_BUTTON::BUTTON_5,
                "BUTTON_6", JOYSTICK_BUTTON::BUTTON_6,
                "BUTTON_7", JOYSTICK_BUTTON::BUTTON_7,
                "BUTTON_8", JOYSTICK_BUTTON::BUTTON_8,
                "BUTTON_9", JOYSTICK_BUTTON::BUTTON_9,
                "BUTTON_10", JOYSTICK_BUTTON::BUTTON_10,
                "BUTTON_11", JOYSTICK_BUTTON::BUTTON_11,
                "BUTTON_12", JOYSTICK_BUTTON::BUTTON_12,
                "BUTTON_13", JOYSTICK_BUTTON::BUTTON_13,
                "BUTTON_14", JOYSTICK_BUTTON::BUTTON_14,
                "BUTTON_15", JOYSTICK_BUTTON::BUTTON_15);
    m_script.new_usertype<STGame>("STGame",
                                "getInput", &STGame::getInput,
                                "getTick", &STGame::getTick,
                                "getDelta", &STGame::getDelta,
                                "getWidth", &STGame::getWidth,
                                "getHeight", &STGame::getHeight,
                                "getCamera", &STGame::getCamera,
                                "Get", &STGame::Get);
    m_script.new_usertype<Camera>("Camera",
                                "getForward", &Camera::getForward,
                                "getUp", &Camera::getUp,
                                "transform", &Camera::transform);
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
    m_script.new_usertype<Vector3D>("Vector3", sol::constructors<sol::types<>, sol::types<stReal, stReal, stReal>>(),
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
                                           "setW", &Vector4<stReal>::setW,
                                           "getX", &Vector4<stReal>::getX,
                                           "getY", &Vector4<stReal>::getY,
                                           "getZ", &Vector4<stReal>::getZ,
                                           "getW", &Vector4<stReal>::getW,
                                           "getLength", &Vector4<stReal>::getLength,
                                           "dot", &Vector4<stReal>::dot,
                                           "toVector3", &Vector4<stReal>::toVector3);
    m_script.new_simple_usertype<STEntity>("STEntity",
                                    "getTag", &STEntity::getTag,
                                    "transform", &STEntity::transform,
                                    "setShdrUniformi", sol::resolve<void(const std::string&, int)>(&STEntity::setShdrUniform),
                                    "setShdrUniformf", sol::resolve<void(const std::string&, float)>(&STEntity::setShdrUniform),
                                    "setShdrUniformV3", sol::resolve<void(const std::string&, Vector3<stReal>)>(&STEntity::setShdrUniform),
                                    "setShdrUniformV4", sol::resolve<void(const std::string&, Vector4<stReal>)>(&STEntity::setShdrUniform),
                                    "setTranslateX", &STEntity::setTranslateX,
                                    "setTranslateY", &STEntity::setTranslateY,
                                    "setTranslateZ", &STEntity::setTranslateZ,
                                    "setRotateX", &STEntity::setRotateX,
                                    "setRotateY", &STEntity::setRotateY,
                                    "setRotateZ", &STEntity::setRotateZ,
                                    "setAttributei", sol::resolve<void(const std::string&, const int&)>(&STEntity::setAttribute),
                                    "setAttributef", sol::resolve<void(const std::string&, const float&)>(&STEntity::setAttribute),
                                    "setAttribute2v", sol::resolve<void(const std::string&, const Vector2<stReal>&)>(&STEntity::setAttribute),
                                    "setAttribute3v", sol::resolve<void(const std::string&, const Vector3<stReal>&)>(&STEntity::setAttribute),
                                    "setAttribute4v", sol::resolve<void(const std::string&, const Vector4<stReal>&)>(&STEntity::setAttribute),
                                    "getAttributei", &STEntity::getAttributei,
                                    "getAttributef", &STEntity::getAttributef,
                                    "getAttribute2v", &STEntity::getAttribute2v,
                                    "getAttribute3v", &STEntity::getAttribute3v,
                                    "getAttribute4v", &STEntity::getAttribute4v);
    m_script.new_simple_usertype<Transform>("Transform", sol::constructors<sol::types<>>(),
                                     "setTranslate", sol::resolve<void(Vector3<stReal>)>(&Transform::setTranslate),
                                     "setTranslateX", &Transform::setTranslateX,
                                     "setTranslateY", &Transform::setTranslateY,
                                     "setTranslateZ", &Transform::setTranslateZ,
                                     "getTranslate", &Transform::getTranslate,
                                     "setRotate", sol::resolve<void(Vector3<stReal>)>(&Transform::setRotate),
                                     "setRotateX", &Transform::setRotateX,
                                     "setRotateY", &Transform::setRotateY,
                                     "setRotateZ", &Transform::setRotateZ,
                                     "getRotate", &Transform::getRotate,
                                     "setScale", sol::resolve<void(Vector3<stReal>)>(&Transform::setScale),
                                     "getScale", &Transform::getScale,
                                     "setRotationMode", &Transform::setRotationMode,
                                     "getForward", &Transform::getForward,
                                     "getUp", &Transform::getUp,
                                     "getRight", &Transform::getRight);
    m_script.script_file(fileName);
    m_script["start"](m_entity);
}

void STScriptComponent::registerEvent(STEntity *self, const std::string &eventName) {
    auto ec = self->get<STEventComponent>();
    if(m_script[eventName].valid()){
        ec->addEvent(eventName, m_script[eventName]);
    }
}

void STScriptComponent::registerFunction(const std::string &functionName, std::function<void()> newFunction) {
    m_script.set_function(functionName.c_str(), newFunction);
}

void STScriptComponent::init(STEntity *parent) {
    this->m_entity = parent;
    this->initScript(this->scriptName);
}

