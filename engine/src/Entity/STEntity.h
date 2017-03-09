#ifndef WAHOO_STENTITY_H
#define WAHOO_STENTITY_H

#include <map>
#include <vector>
#include <typeindex>
#include "../Math/Transform.h"
#include "Components/STComponent.h"
#include "Components/STGraphicsComponent.h"
#include "Components/STMeshComponent.h"
#include "Components/STScriptComponent.h"
#include "../Math/Matrix.h"
#include "../Graphics/STGraphics.h"

class Transform;
class Camera;
class STGraphics;
class STComponent;
class STMeshComponent;
class STGraphicsComponent;
class STScriptComponent;

struct STAttribute{
    enum Type{
        Int = 0,
        Float = 1,
        Double = 2,
        String = 3,
        Vector3 = 4,
        Vector4 = 5
    };
    STAttribute(const int value){
        type = Int;

    }

    STAttribute(const float value){

    }
private:
    Type type;
    std::string value;
};

class STEntity {
public:
    enum Type{
        Actor = 0,
        Light = 1,
        GUI = 2
    };

    /**
     * Default Constructor
     * @return new STEntity
     */
    STEntity();

    /** Creates new STEntity.
     *
     * @param fileName - Path to model file
     * @param type - File Format
     * @param shdr - Specified Shader
     * @return
     */
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
    void addScriptComponent(const std::string& script);
    void addChild(STEntity* entity);
    STEntity* getChild(int ind);

    inline bool hasChildren(){ return m_children.size() > 0; }

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

    void addShdrUniform(const std::string& name, int value);
    void addShdrUniform(const std::string& name, float value);
    void addShdrUniform(const std::string& name, Vector3<stReal> value);
    void addShdrUniform(const std::string& name, Vector4<stReal> value);
    void addShdrUniform(const std::string& name, Matrix4f value);
    void addShdrUniform_Texture(const std::string& name, stUint tag);
    void addShdrUniform_CubeMap(const std::string& name, stUint tag);
    void setDiffuseTexture(const std::string& fileName);
    void setNormalTexture(const std::string& fileName);

    void setShdrUniform(const std::string& name, int value);
    void setShdrUniform(const std::string& name, float value);
    void setShdrUniform(const std::string& name, Vector3<stReal> value);
    void setShdrUniform(const std::string& name, Vector4<stReal> value);
    void setShdrUniform(const std::string& name, Matrix4f value);
    void setShdrUniform_Texture(const std::string& name, stUint id, stUint index);
    void setShdrUniform_Texture(const std::string& name, stUint tag);
    void setShdrUniform_CubeMap(const std::string& name, stUint tag);

    STEntity* childAtTag(const std::string& tag);
    inline stUint getChildSize(){ return m_children.size(); }

    inline void setTag(const std::string& name){ m_tag = name; }

    std::string getTag()const{ return m_tag; }

    void setVisible(bool value);
    bool isVisible();

    template<typename T> inline T* get(){
        auto it = m_components.find(std::type_index(typeid(T)));
        if(it != m_components.end()){
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    inline Transform* transform(){ return m_transform; }

    virtual void update();

    virtual void draw(){
        auto grphx = get<STGraphicsComponent>();
        auto mesh = get<STMeshComponent>();
        grphx->draw();
        mesh->draw();
        if(hasChildren()){
            for(unsigned int i = 0, lim = (unsigned int)m_children.size(); i < lim; i++){
                m_children.at(i)->draw();
            }
        }
    }

    virtual void draw(STGraphics* grphx);

    void draw(Camera* cam){
        auto grphx = this->get<STGraphicsComponent>();
        auto mesh = this->get<STMeshComponent>();
        grphx->draw();
        grphx->shdr()->update(*m_transform, *cam);
        mesh->draw();
        if(hasChildren()){
            for(unsigned int i = 0, lim = (unsigned int)m_children.size(); i < lim; i++){
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
            for(unsigned int i = 0, lim = (unsigned int)m_children.size(); i < lim; i++){
                m_children.at(i)->draw(cam, drawMode);
            }
        }
    }

protected:
    Type m_type;
    std::string m_tag;
    Transform* m_transform;
    bool m_visible;
    std::map<std::type_index, STComponent*> m_components;
    std::map<std::string, STAttribute*> m_attributes;
    std::vector<STEntity*> m_children;
};


#endif //WAHOO_STENTITY_H
