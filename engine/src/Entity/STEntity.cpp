#include "STEntity.h"
#include "Components/STEventComponent.h"
#include "Components/STAABBComponent.h"

STEntity::STEntity() {
    m_transform = new Transform();
}

STEntity::~STEntity() {
    delete m_transform;
    m_transform = 0;
    m_components.clear();
}

void STEntity::addComponent(std::type_index type, STComponent *component) {
    m_components[type] = component;
    m_components[type]->init(this);
}

void STEntity::addChild(STEntity *entity) {
    m_children.push_back(entity);
}

STEntity* STEntity::getChild(int ind) {
    auto ret = m_children.at(ind);
    if(ret == nullptr) return nullptr;
    return ret;
}

STEntity *STEntity::childAtTag(const std::string &tag) {
    for(auto ent : m_children){
        if(ent->m_tag == tag) return ent;
    }
    return nullptr;
}

void STEntity::addScriptComponent(const std::string &script) {
    addComponent(typeid(STScriptComponent*), new STScriptComponent(this, script));
}

//Start moving to this method of drawing
void STEntity::draw(STGraphics *grphx) {
    auto graphics = this->get<STGraphicsComponent>();
    auto mesh = this->get<STMeshComponent>();
    auto camera = grphx->getActiveCamera();

    graphics->draw();
    graphics->shdr()->update(*m_transform, *camera);
    mesh->draw();

    graphics->draw();
}

void STEntity::setVisible(bool value) {
    m_visible = value;
}

bool STEntity::isVisible() {
    return m_visible;
}

void STEntity::update() {
    for(auto comp : m_components){
        comp.second->update();
    }
}

void STEntity::addAttribute(const std::string &name, const int &value) {
    m_attributes.insert(std::pair<std::string, STAttribute*>(name, new STAttribute(value)));
}

void STEntity::addAttribute(const std::string &name, const float &value) {
    m_attributes.insert(std::pair<std::string, STAttribute*>(name, new STAttribute(value)));
}

void STEntity::addAttribute(const std::string &name, const Vector2<stReal> &value) {
    m_attributes.insert(std::pair<std::string, STAttribute*>(name, new STAttribute(value)));
}

void STEntity::addAttribute(const std::string &name, const Vector3<stReal> &value) {
    m_attributes.insert(std::pair<std::string, STAttribute*>(name, new STAttribute(value)));
}

void STEntity::addAttribute(const std::string &name, const Vector4<stReal> &value) {
    m_attributes.insert(std::pair<std::string, STAttribute*>(name, new STAttribute(value)));
}

void STEntity::setAttribute(const std::string &name, const int &value) {
    if(m_attributes.count(name) > 0){
        m_attributes[name]->m_value = STAttribute::toString(value);
        return;
    }
    addAttribute(name, value);
}

void STEntity::setAttribute(const std::string &name, const float &value) {
    if(m_attributes.count(name) > 0){
        m_attributes[name]->m_value = STAttribute::toString(value);
        return;
    }
    addAttribute(name, value);
}

void STEntity::setAttribute(const std::string &name, const Vector2<stReal> &value) {
    if(m_attributes.count(name) > 0){
        m_attributes[name]->m_value = STAttribute::toString(value);
        return;
    }
    addAttribute(name, value);
}

void STEntity::setAttribute(const std::string &name, const Vector3<stReal> &value) {
    if(m_attributes.count(name) > 0){
        m_attributes[name]->m_value = STAttribute::toString(value);
        return;
    }
    addAttribute(name, value);
}

void STEntity::setAttribute(const std::string &name, const Vector4<stReal> &value) {
    if(m_attributes.count(name) > 0){
        m_attributes[name]->m_value = STAttribute::toString(value);
        return;
    }
    addAttribute(name, value);
}

int STEntity::getAttributei(const std::string &name) const {
    if(m_attributes.count(name) > 0){
        return m_attributes.at(name)->toInt();
    }
    return 10001;
}

float STEntity::getAttributef(const std::string &name) const {
    if(m_attributes.count(name) > 0){
        return m_attributes.at(name)->toFloat();
    }
    return 10001;
}

Vector2<stReal> STEntity::getAttribute2v(const std::string &name) const {
    if(m_attributes.count(name) > 0) return m_attributes.at(name)->toVector2();
}

Vector3<stReal> STEntity::getAttribute3v(const std::string &name) const {
    if(m_attributes.count(name) > 0) return m_attributes.at(name)->toVector3();
}

Vector4<stReal> STEntity::getAttribute4v(const std::string &name) const {
    if(m_attributes.count(name) > 0) return m_attributes.at(name)->toVector4();
}

void STEntity::dispose() {
    for(auto comp : m_components){
        comp.second->dispose();
    }
    m_components.clear();
}

const std::map<std::type_index, STComponent *> &STEntity::getAllComponents() const {
    return m_components;
}

STAttribute::STAttribute(const Vector2<stReal> &value){
    type = Vec2;
    m_value = STAttribute::toString(value);
}

STAttribute::STAttribute(const Vector3<float> &value) {
    type = Vec3;
    m_value = STAttribute::toString(value);
}

STAttribute::STAttribute(const Vector4<stReal> &value) {
    type = Vec4;
    m_value = toString(value);
}

std::string STAttribute::toString(const Vector2<stReal> &vec) {
    std::ostringstream buff;
    buff << vec.getX() << "/" << vec.getY();
    return buff.str();
}

std::string STAttribute::toString(const Vector3<stReal> &vec) {
   std::ostringstream buff;
    buff << vec.getX() << "/" << vec.getY() << "/" << vec.getZ();
    return buff.str();
}

std::string STAttribute::toString(const Vector4<stReal> &vec) {
    std::ostringstream buff;
    buff << vec.getX() << "/" << vec.getY() << "/" << vec.getZ() << "/" << vec.getW();
    return buff.str();
}

std::string STAttribute::toString(const float &value) {
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

std::string STAttribute::toString(const int &value) {
    std::ostringstream stream;
    stream << value;
    return stream.str();
}

STAttribute::STAttribute(const int &value) {
    type = Int;
    m_value = STAttribute::toString(value);
}

STAttribute::STAttribute(const float &value) {
    type = Float;
    m_value = STAttribute::toString(value);
}

STAttribute::STAttribute(const std::string &value) {
    type = String;
    m_value = value;
}

int STAttribute::toInt() const {
    if(type == Int) return atoi(m_value.c_str());
    return 10001;
}

float STAttribute::toFloat() const {
    if(type == Float) return (float)atof(m_value.c_str());
    return 10001;
}

Vector2<stReal> STAttribute::toVector2() const {
    if(type == Vec2){
        stReal _x = 0, _y = 0;
        std::string val = m_value;
        _x = (stReal)atof(val.substr(0, val.find('/')).c_str());
        _y = (stReal)atof(val.substr(val.find('/')+1).c_str());
        return Vector2<stReal>(_x, _y);
    }
}

Vector3<stReal> STAttribute::toVector3() const {
    if(type == Vec3){
        auto val = m_value;
        stReal _x = 0;
        stReal _y = 0;
        stReal _z = 0;
        _x = (stReal)atof(val.substr(0, val.find('/')).c_str());
        _y = (stReal)atof(val.substr(val.find('/')+1, val.find_last_of('/') ).c_str());
        _z = (stReal)atof(val.substr(val.find_last_of('/')+1).c_str());
        return Vector3<stReal>(_x, _y, _z);
    }
}

Vector4<stReal> STAttribute::toVector4() const {
    if(type == Vec4){
        auto value = m_value;
        stReal _x = 0, _y = 0, _z = 0, _w = 0;
        std::string vX = value.substr(0, value.find('/'));
        std::string d1 = value.substr(value.find('/')+1);
        std::string vY = d1.substr(0, d1.find('/'));
        std::string d2 = d1.substr(d1.find('/')+1);
        std::string vZ = d2.substr(0, d2.find('/'));
        std::string vW = d2.substr(d2.find_last_of('/')+1);
        _x = (stReal)atof(vX.c_str());
        _y = (stReal)atof(vY.c_str());
        _z = (stReal)atof(vZ.c_str());
        _w = (stReal)atof(vW.c_str());
        return Vector4<stReal>(_x, _y, _z, _w);
    }
}


