#include "Transform.h"
#include "STEntity.h"

Transform::Transform(STEntity *parent) {
    this->parent = parent;
    this->translate = Vector3<stReal>(0.f, 0.f, 0.f);
    rotate = Vector3<stReal>(0.0f, 0.0f, 0.0f);
    scale = Vector3<stReal>(1.0f, 1.0f, 1.0f);
    rotateMode = Local;
}

void Transform::setTranslate(Vector3<stReal> &vec) {
    this->translate = vec;
    if(parent != nullptr){
        if(parent->hasChildren()){
            for(auto child : parent->getChildren()){
                auto childPos = child->transform()->getTranslate();
                childPos = childPos + vec;
                child->transform()->setTranslate(childPos);
            }
        }
    }
}

void Transform::setTranslateX(stReal _x) {
    this->translate.setX(_x);
    if(parent != nullptr && parent->hasChildren()){
        for(auto child : parent->getChildren()){
            stReal cX = child->transform()->getTranslate().getX();
            cX += _x;
            child->transform()->setTranslateX(cX);
        }
    }
}

void Transform::setTranslateY(stReal _y) {
    this->translate.setY(_y);
    if(parent != nullptr && parent->hasChildren()){
        for(auto child : parent->getChildren()){
            stReal cY = child->transform()->getTranslate().getY() + _y;
            child->transform()->setTranslateY(cY);
        }
    }
}

void Transform::setTranslateZ(stReal _z) {
    this->translate.setZ(_z);
    if(parent != nullptr && parent->hasChildren()){
        for(auto child : parent->getChildren()){
            child->transform()->setTranslateZ(child->transform()->getTranslate().getZ() + _z);
        }
    }
}

const Matrix4f Transform::getModel() const {
    Matrix4f trans, rot, scaleMat;
    trans.initTranslation(translate);
    if(rotateMode == Global){
        rot.initRotate(rotate);
    }else{
        Matrix4f negTransMat;
        negTransMat.initTranslation(-translate.getX(), -translate.getY(), -translate.getZ());
        rot.initRotate(rotate);
        rot = trans * rot * negTransMat;
    }
    scaleMat.initScale(scale);

    Matrix4f ret;
    ret = scaleMat * rot * trans;
    return ret;
}

void Transform::setTranslate(stReal _value) {
    setTranslateX(_value);
    setTranslateY(_value);
    setTranslateZ(_value);
}

void Transform::setRotate(Vector3<stReal> &vec) {
    this->rotate = vec;
}

void Transform::setRotateX(stReal _x) {
    rotate.setX(_x);
}

void Transform::setRotateZ(stReal _z) {
    rotate.setZ(_z);
}

void Transform::setRotateY(stReal _y) {
    rotate.setY(_y);
}

std::string Transform::getInfo() {
    Matrix4f mat = getModel();
    return mat.getInfo();
}

Json Transform::to_json() const {
    return Json::object{
            {
                "Transform", Json::object{
                {"translate", translate},
                {"rotate", rotate},
                {"scale", scale},
                {"rotationMode", (rotateMode == Global) ? 0 : 1}
                }
            }

    };
}

Transform *Transform::FromJson(const std::string &jsonFile) {
    std::ifstream in(jsonFile);
    std::stringstream readBuff;
    readBuff << in.rdbuf();
    in.close();
    std::string errStr;
    Json doc = Json::parse(readBuff.str(), errStr, JsonParse::STANDARD);
    return Transform::FromJson(doc);
}

Transform *Transform::FromJson(const Json doc) {
    auto ret = new Transform();
    for(auto key : doc["Transform"].object_items()){
        auto vec = Vector3<stReal>::FromJson(key.second);
        if(key.first == "translate"){
            ret->setTranslate(vec);
        }else if(key.first == "rotate"){
            ret->setRotate(vec);
        }else if(key.first == "scale"){
            ret->setScale(vec);
        }else if(key.first == "rotationMode"){
            ret->rotateMode = (key.second.int_value() == 0) ? Global : Local;
        }
    }
    return ret;

}

Transform::Transform() {
    parent = nullptr;
    translate = Vector3D(0.0f, 0.0f, 0.0f);
    rotate = Vector3D(0.0f, 0.0f, 0.0f);
    scale = Vector3D(1.0f, 1.0f, 1.0f);
    rotateMode = Global;
}

Transform::Transform(Vector3D &translate, Vector3D &rotate, Vector3D scale) {
    parent = nullptr;
    this->translate = translate;
    this->rotate = rotate;
    this->scale = scale;
    rotateMode = Global;
}

void Transform::setScale(stReal _value) {
    setScaleX(_value);
    setScaleY(_value);
    setScaleZ(_value);
}

void Transform::setRotationMode(Transform::RotationMode rotMode) {
    rotateMode = rotMode;
}

Transform::Transform(STEntity *parent, Vector3D &translate, Vector3D &rotate, Vector3D &scale) {
    this->parent = parent;
    this->translate = translate;
    this->rotate = rotate;
    this->scale = scale;
    rotateMode = Global;
}

void Transform::setScale(Vector3D &vec) { this->scale = vec; }

void Transform::setScaleZ(stReal _z) { this->scale.setZ(_z); }

void Transform::setScaleX(stReal _x) { this->scale.setX(_x); }

void Transform::setScaleY(stReal _y) { this->scale.setY(_y); }

Vector3D Transform::getForward() const {
    auto rot = Matrix4f().initRotate(rotate);
    return Vector3D(rot.m[2][0], rot.m[2][1], rot.m[2][2]);
}

Vector3D Transform::getUp() const {
    auto rot = Matrix4f().initRotate(rotate);
    return Vector3D(rot.m[1][0], rot.m[1][1], rot.m[1][2]);
}

Vector3D Transform::getRight() const {
    auto rot = Matrix4f().initRotate(rotate);
    return Vector3D(rot.m[0][0], rot.m[0][1], rot.m[2][2]);
}
