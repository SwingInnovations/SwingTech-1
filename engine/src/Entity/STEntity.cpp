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

void STEntity::setTranslate(Vector3<stReal> &vec) {
    this->setTranslateX(vec.getX());
    this->setTranslateY(vec.getY());
    this->setTranslateZ(vec.getZ());
    if(!m_children.empty()){
        for(STEntity* entity : m_children){
            Vector3<stReal> childPosition = entity->transform()->getTranslate();
            childPosition = childPosition + vec;
            entity->setTranslate(childPosition);
        }
    }
}

void STEntity::setTranslate(stReal _value){
    this->setTranslateX(_value);
    this->setTranslateY(_value);
    this->setTranslateZ(_value);
    if(!m_children.empty()){
        for(auto entity : m_children){
            Vector3<stReal> childPosition = entity->transform()->getTranslate();
            childPosition = childPosition + _value;
            entity->setTranslate(childPosition);
        }
    }

}

void STEntity::setTranslateX(stReal _x) {
    m_transform->setTranslateX(_x);
    if(!m_children.empty()){
        for(auto entity : m_children){
            stReal cX = entity->transform()->getTranslate().getX();
             cX += _x;
            entity->setTranslateX(_x);
        }
    }

}

void STEntity::setTranslateY(stReal _y) {
    m_transform->setTranslateY(_y);
    if(!m_children.empty()){
        for(auto entity : m_children){
            stReal cY = entity->transform()->getTranslate().getY();
            cY += _y;
            entity->setTranslateY(_y);
        }
    }
}

void STEntity::setTranslateZ(stReal _z){
    m_transform->setTranslateZ(_z);
    if(!m_children.empty()){
        for(auto entity : m_children){
            stReal cZ = entity->transform()->getTranslate().getZ();
            cZ += _z;
            entity->setTranslateZ(_z);
        }
    }
}

void STEntity::setRotate(Vector3<stReal> &vec) {
    setRotateX(vec.getX());
    setRotateY(vec.getY());
    setRotateZ(vec.getZ());
}

void STEntity::setRotateX(stReal _x) {
    m_transform->setRotateX(_x);
}

void STEntity::setRotateY(stReal _y){
    m_transform->setRotateY(_y);
}

void STEntity::setRotateZ(stReal _z) {
    m_transform->setRotateZ(_z);
}


void STEntity::setScale(Vector3<stReal> &vec) {
    m_transform->setScale(vec);
}

void STEntity::setScale(stReal _value) {
    m_transform->setScale(_value);
}

void STEntity::setScaleX(stReal _x) {
    m_transform->setScale(_x);
}

void STEntity::setScaleY(stReal _y) {
    m_transform->setScaleY(_y);
}

void STEntity::setScaleZ(stReal _z) {
    m_transform->setScaleZ(_z);
}

void STEntity::addShdrUniform(const std::string &name, int value) {
    get<STGraphicsComponent>()->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string &name, float value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string &name, Vector2<stReal> value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr){ grphx->addShdrUniform(name, value); }
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string& name, Vector3<stReal> value){
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string &name, Vector4<stReal> value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->addShdrUniform(name, value);
        }
    }
}

void STEntity::addShdrUniform(const std::string &name, Matrix4f value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children) child->addShdrUniform(name, value);
    }
}

void STEntity::addShdrUniform_Texture(const std::string &name, stUint tag) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->addShdrUniform_Texture(name, tag);
    if(hasChildren()){
        for(auto child : m_children) child->addShdrUniform_Texture(name, tag);
    }
}

void STEntity::addShdrUniform_CubeMap(const std::string &name, stUint tag) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->addShdrUniform_CubeMap(name, tag);
    if(hasChildren()){
        for(auto child : m_children) child->addShdrUniform_CubeMap(name, tag);
    }
}

void STEntity::setShdrUniform(const std::string &name,int value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->addShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, float value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, Vector2<stReal> value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, Vector3<stReal> value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, Vector4<stReal> value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children){
            child->setShdrUniform(name, value);
        }
    }
}

void STEntity::setShdrUniform(const std::string &name, Matrix4f value) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->setShdrUniform(name, value);
    if(hasChildren()){
        for(auto child : m_children) child->setShdrUniform(name, value);
    }
}

void STEntity::setShdrUniform_Texture(const std::string &name, stUint tag) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->setShdrUniform_Texture(name, tag);
    if(hasChildren()){
        for(auto child : m_children) child->setShdrUniform_Texture(name, tag);
    }
}

void STEntity::setShdrUniform_CubeMap(const std::string &name, stUint tag) {
    auto grphx = get<STGraphicsComponent>();
    if(grphx != nullptr) grphx->setShdrUniform_CubeMap(name, tag);
    if(hasChildren()){
        for(auto child : m_children) child->setShdrUniform_CubeMap(name, tag);
    }
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

void STEntity::setDiffuseTexture(const std::string &fileName) {
    auto g = get<STGraphicsComponent>();
    if(g != nullptr) g->setDiffuseTexture(fileName);
    if(hasChildren()){
        for(auto child : m_children){
            child->setDiffuseTexture(fileName);
        }
    }
}

void STEntity::setNormalTexture(const std::string &fileName) {
    auto g = get<STGraphicsComponent>();
    if(g != nullptr) g->setNormalTexture(fileName);
    if(hasChildren()){
        for(auto child : m_children){
            child->setNormalTexture(fileName);
        }
    }
}

void STEntity::setShdrUniform_Texture(const std::string &name, stUint id, stUint index) {
    auto g = get<STGraphicsComponent>();
    if(g != nullptr) g->setShdrUniform_Texture(name, id, index);
}

void STEntity::setShdrUniform_Texture2DArray(const std::string &name, stUint id, stUint index) {
    auto g = get<STGraphicsComponent>();
    if(g != nullptr) g->setShdrUniform_Texture2DArray(name, id, index);
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
        Vector3<stReal> ret(_x, _y, _z);
        return ret;
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
        Vector4<stReal> ret(_x, _y, _z, _w);
        return ret;
    }
}


