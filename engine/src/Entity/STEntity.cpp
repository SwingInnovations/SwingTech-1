#include "STEntity.h"
#include "Components/STEventComponent.h"
#include "Components/STAABBComponent.h"
#include "../Application/Util/File/STSerializeable.h"

STEntity::STEntity() {
    m_transform = std::make_shared<Transform>();
    numComponents = 0;
}

STEntity::~STEntity() {
    for(auto comp : m_components){
        delete comp.second;
    }
    m_components.clear();
}

void STEntity::addComponent(std::type_index type, STComponent* component) {
    auto t = shared_from_this();
    std::string key;
#if _MSC_VER > 1900
    key = STSerializableUtility::SanitizeStringMSVC(type.name());
#else
    int status;
    key = abi::__cxa_demangle(type.name(), 0, 0, &status);
#endif
    m_components[key] = component;
    m_components[key]->init(t);
    numComponents++;
}

void STEntity::addChild(STEntity *entity) {
    //m_children.push_back(entity);
}

STEntity* STEntity::getChild(int ind) {
    auto ret = m_children.at(ind);
    if(ret == nullptr) return nullptr;
    return ret.get();
}

STEntity *STEntity::childAtTag(const std::string &tag) {
    for (auto ent : m_children) {
        if (ent->m_tag == tag) return ent.get();
    }
    return nullptr;
}

//Start moving to this method of drawing
void STEntity::draw(STGraphics *grphx) {
    auto graphics = this->get<STRendererComponent>();
    auto mesh = this->get<STMeshComponent>();
    auto Camera = grphx->getCamera();

    graphics->draw();
    graphics->getMaterial()->shdr()->update(*m_transform, Camera);
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
        if(!m_components.empty()){
            comp.second->update();
        }
    }
}

void STEntity::addAttribute(const std::string &name, const int &value) {
    m_attributes.insert(std::pair<std::string, std::shared_ptr<STAttribute>>(name, std::make_shared<STAttribute>(value)));
}

void STEntity::addAttribute(const std::string &name, const float &value) {
    m_attributes.insert(std::pair<std::string, std::shared_ptr<STAttribute>>(name, std::make_shared<STAttribute>(value)));
}

void STEntity::addAttribute(const std::string &name, const Vector2<stReal> &value) {
    m_attributes.insert(std::pair<std::string, std::shared_ptr<STAttribute>>(name, std::make_shared<STAttribute>(value)));
}

void STEntity::addAttribute(const std::string &name, const Vector3<stReal> &value) {
    m_attributes.insert(std::pair<std::string, std::shared_ptr<STAttribute>>(name, std::make_shared<STAttribute>(value)));
}

void STEntity::addAttribute(const std::string &name, const Vector4<stReal> &value) {
    m_attributes.insert(std::pair<std::string, std::shared_ptr<STAttribute>>(name, std::make_shared<STAttribute>(value)));
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

const std::map<std::string, STComponent*> &STEntity::getAllComponents() const {
    return m_components;
}

void STEntity::draw(Camera *cam, int drawMode) {
    auto grphx = this->get<STRendererComponent>();
    auto mesh = this->get<STMeshComponent>();
    grphx->draw();
    grphx->getMaterial()->shdr()->update(*m_transform, *cam);
    mesh->draw(drawMode);

    if(hasChildren()){
        for (auto &child : m_children) {
            child->draw(cam, drawMode);
        }
    }
}

void STEntity::draw(Camera *cam) {
    auto grphx = this->get<STRendererComponent>();
    auto mesh = this->get<STMeshComponent>();
    grphx->draw();
    grphx->getMaterial()->shdr()->update(*m_transform, *cam);
    mesh->draw();
    if(hasChildren()){
        for (auto &i : m_children) {
            i->draw(cam);
        }
    }
}

void STEntity::draw() {
    auto grphx = get<STRendererComponent>();
    auto mesh = get<STMeshComponent>();
    grphx->draw();
    mesh->draw();
    if(hasChildren()){
        for (auto &child : m_children) {
            child->draw();
        }
    }
}

void STEntity::init() {
    m_transform = std::make_shared<Transform>();
    m_transform->setEntity(shared_from_this());
}

void STEntity::setParent(std::shared_ptr<STEntity> p) {
    this->m_parent = p;
}

void STEntity::load(std::ifstream &in) {
    auto t = shared_from_this();
    stUint childCount = 0, attribCount = 0;
    m_name = STSerializableUtility::ReadString(in);
    m_tag = STSerializableUtility::ReadString(in);
    m_transform->load(in);
    in.read((char*)&childCount, sizeof(stUint));
    in.read((char*)&numComponents, sizeof(numComponents));
    in.read((char*)&attribCount, sizeof(stUint));
    for(stUint i = 0; i < numComponents; i++){
        auto componentName = STSerializableUtility::ReadString(in);
        auto comp = STComponentObjectFactory::Get()->create(componentName);
		if (comp != nullptr) {
			comp->init(t);
			comp->load(in);
			m_components[componentName] = comp;
		}
    }

    for(stUint i = 0; i < childCount; i++){
        auto child = std::make_shared<STEntity>();
        child->load(in);
        m_children.emplace_back(child);
    }

    for(stUint i = 0; i < attribCount; i++){
        auto key = STSerializableUtility::ReadString(in);
        auto value = std::make_shared<STAttribute>();
        value->load(in);
        m_attributes[key] = value;
    }
}

void STEntity::save(std::ofstream &out) {
    STSerializableUtility::WriteString(m_name.c_str(), out);
    STSerializableUtility::WriteString(m_tag.c_str(), out);
    auto childCount = (stUint)m_children.size();
    auto attribCount = (stUint)m_attributes.size();
    m_transform->save(out);
    out.write((char*)&childCount, sizeof(stUint));
    out.write((char*)&numComponents, sizeof(numComponents));
    out.write((char*)&attribCount, sizeof(stUint));
    for(auto comp : m_components) {
        auto compName = comp.first.c_str();
        STSerializableUtility::WriteString(compName, out);
        comp.second->save(out);
    }

    for(const auto child : m_children){
        child->save(out);
    }

    for(const auto attrib : m_attributes){
        STSerializableUtility::WriteString(attrib.first.c_str(), out);
        attrib.second->save(out);
    }
}

void STEntity::_addComponent(const std::string &requestedComponent) {
    auto comp = STComponentObjectFactory::Get()->create(requestedComponent);
    if(comp != nullptr){
        auto t = shared_from_this();
        comp->init(t);
        m_components[requestedComponent] = comp;
    }
}

STEntity::Type STEntity::getType() const {
    return m_type;
}

void STEntity::addScript(const std::string& name) {
    addComponent<STScriptComponent>(new STScriptComponent(name));
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

void STAttribute::save(std::ofstream &out) {
    out.write((char*)&type, sizeof(type));
    STSerializableUtility::WriteString(m_value.c_str(), out);
}

void STAttribute::load(std::ifstream &in) {
    stUint dataSize = 0;
    in.read((char*)&type, sizeof(type));
    m_value = STSerializableUtility::ReadString(in);
}

STAttribute::STAttribute() = default;



