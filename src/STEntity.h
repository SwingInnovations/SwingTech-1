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
    ~STEntity();

    void addComponent(std::type_index, STComponent*);

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
    }

    void draw(Camera* cam){
        auto grphx = this->get<STGraphicsComponent>();
        auto mesh = this->get<STMeshComponent>();
        grphx->draw();
        grphx->shdr()->update(*m_transform, *cam);
        mesh->draw();
        //grphx->shdr()->unbind();
    }

    void draw(Camera* cam, int drawMode){
        auto grphx = this->get<STGraphicsComponent>();
        auto mesh = this->get<STMeshComponent>();
        grphx->draw();
        grphx->shdr()->update(*m_transform, *cam);
        mesh->draw(drawMode);
    }
private:
    bool m_hasChildren;
    Transform* m_transform;
    std::map<std::type_index, STComponent*> m_components;
    std::vector<STEntity*> m_children;
};


#endif //WAHOO_STENTITY_H
