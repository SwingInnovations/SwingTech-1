#ifndef WAHOO_STENTITY_H
#define WAHOO_STENTITY_H

#include <map>
#include <vector>
#include <typeindex>
#include "Math/Transform.h"
#include "STComponent.h"
#include "STGraphicsComponent.h"
#include "STMeshComponent.h"
#include "Math/Matrix.h"

class Transform;
class Camera;
class STComponent;
class STMeshComponent;
class STGraphicsComponent;

class STEntity {
public:
    STEntity();
    STEntity(const std::string& fileName, const int type, Shader* shdr);
    STEntity(const std::string& fileName, const int type, const std::string& shdrPath);
    STEntity(const std::string& fileName, const int type, const std::string& shdrPath, const std::string texPath);
    STEntity(const std::string& fileName, const int type, Shader* shdr, Texture* tex);
    STEntity(const std::string& fileName, const int type, STMaterial* mat);
    STEntity(STRect*,Shader*);
    STEntity(STQuad*,Shader*);
    STEntity(STCube*,Shader*);
    STEntity(STCube*,Shader*, Texture*);
    ~STEntity();

    void addComponent(std::type_index, STComponent*);
    void addChild(STEntity* entity);
    STEntity* getChild(int ind);

    bool hasChildren(){ return m_children.size() > 0; }

    //Overload Transforms
    void setTranslate(Vector3<stReal>& vec);
    void setTranslate(stReal _value);
    void setTranslateX(stReal _x);
    void setTranslateY(stReal _y);
    void setTranslateZ(stReal _z);

    void setRotate(Vector3<stReal>& vec);
    void setRotateX(stReal _x);
    void setRotateY(stReal _y);
    void setRotateZ(stReal _z);

    void setScale(Vector3<stReal>& vec);
    void setScale(stReal _value);
    void setScaleX(stReal _x);
    void setScaleY(stReal _y);
    void setScaleZ(stReal _z);

    void addShdrAttrib(const std::string& name, int value);
    void addShdrAttrib(const std::string& name, float value);
    void addShdrAttrib(const std::string& name, Vector3<stReal> value);
    void addShdrAttrib(const std::string& name, Vector4<stReal> value);

    void setShdrAttrib(const std::string& name, int value);
    void setShdrAttrib(const std::string& name, float value);
    void setShdrAttrib(const std::string& name, Vector3<stReal> value);
    void setShdrAttrib(const std::string& name, Vector4<stReal> value);

    STEntity* childAtTag(const std::string& tag);

    template<typename T> T* get(){
        auto it = m_components.find(std::type_index(typeid(T)));
        if(it != m_components.end()){
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    Transform* transform(){ return m_transform; }

    void BtSUpdate(STGame *, int);

    void update(STGame * window){

    }

    void draw(){
        auto grphx = get<STGraphicsComponent>();
        auto mesh = get<STMeshComponent>();
        grphx->draw();
        mesh->draw();
        if(hasChildren()){
            for(unsigned int i = 0, lim = m_children.size(); i < lim; i++){
                m_children.at(i)->draw();
            }
        }
    }

    void draw(Camera* cam){
        auto grphx = this->get<STGraphicsComponent>();
        auto mesh = this->get<STMeshComponent>();
        grphx->draw();
        grphx->shdr()->update(*m_transform, *cam);
        mesh->draw();
        if(hasChildren()){
            for(unsigned int i = 0, lim = m_children.size(); i < lim; i++){
                m_children.at(i)->draw(cam);
            }
        }
    }

    void draw(Camera* cam, int drawMode){
        auto grphx = this->get<STGraphicsComponent>();
        auto mesh = this->get<STMeshComponent>();
        grphx->draw();
        grphx->shdr()->update(*m_transform, *cam);
        mesh->draw(drawMode);

        if(hasChildren()){
            for(unsigned int i = 0, lim = m_children.size(); i < lim; i++){
                m_children.at(i)->draw(cam, drawMode);
            }
        }
    }
private:
    std::string tag;
    Transform* m_transform;
    std::map<std::type_index, STComponent*> m_components;
    std::vector<STEntity*> m_children;
};


#endif //WAHOO_STENTITY_H
