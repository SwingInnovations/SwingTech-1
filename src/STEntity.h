#ifndef WAHOO_STENTITY_H
#define WAHOO_STENTITY_H

#include <map>
#include <typeindex>
#include "Math/Transform.h"
#include "STComponent.h"
#include "STGraphicsComponent.h"
#include "STMeshComponent.h"

class Transform;
class Camera;
class STComponent;
class STMeshComponent;
class STGraphicsComponent;

class STEntity {
public:
    STEntity();

    void addComponent(std::type_index, STComponent*);

    template<typename T> T* get(){
        auto it = m_componenets.find(std::type_index(typeid(T)));
        if(it != m_componenets.end()){
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    Transform* transform(){ return m_transform; }

    void draw(){
        auto grphx = get<STGraphicsComponent>();
        auto mesh = get<STMeshComponent>();
        grphx->draw();
        mesh->draw();
    }

    void draw(Camera* cam){
        auto grphx = get<STGraphicsComponent>();
        auto mesh = get<STMeshComponent>();
        grphx->shdr()->update(*m_transform, *cam);
        grphx->draw();
        mesh->draw();
    }
private:
    Transform* m_transform;
    std::map<std::type_index, STComponent*> m_componenets;
};


#endif //WAHOO_STENTITY_H
