#ifndef WAHOO_STENTITY_H
#define WAHOO_STENTITY_H

#include <map>
#include <vector>
#include <memory>
#include <typeindex>
#if _MSC_VER > 1900

#else
#include <cxxabi.h>
#endif
#include <string>

#include "../Math/Vector.h"
#include "Transform.h"
#include "Components/STComponent.h"
#include "Components/STRendererComponent.h"
#include "Components/STMeshComponent.h"
#include "Components/STScriptComponent.h"
#include "../Math/Matrix.h"
#include "../Graphics/STGraphics.h"

class Transform;
class Camera;
class STGraphics;
class STComponent;
class STMeshComponent;
class STRendererComponent;
class STScriptComponent;

/**
 * Attributes that can be attached to entities.
 */
struct STAttribute{
    enum Type{
        Int = 0,
        Float = 1,
        String = 2,
        Vec2 = 3,
        Vec3 = 4,
        Vec4 = 5
    };
    static std::string toString(const int& value);
    static std::string toString(const float& value);
    static std::string toString(const Vector2<stReal>& vec);
    static std::string toString(const Vector3<stReal>& vec);
    static std::string toString(const Vector4<stReal>& vec);

    STAttribute();

    explicit STAttribute(const int& value);
    explicit STAttribute(const float& value);
    explicit STAttribute(const std::string& value);
    explicit STAttribute(const Vector2<stReal> &value);
    explicit STAttribute(const Vector3<stReal> &value);
    explicit STAttribute(const Vector4<stReal>& value);

    int toInt()const;
    float toFloat()const;
    Vector2<stReal> toVector2()const;
    Vector3<stReal> toVector3()const;
    Vector4<stReal> toVector4()const;

    void save(std::ofstream& out);
    void load(std::ifstream& in);

    Type type;
    std::string m_value;
};

class STEntity : public std::enable_shared_from_this<STEntity>{
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

    ~STEntity();
    void init();

    Type getType()const;

    void addComponent(std::type_index, STComponent*);
    void _addComponent(const std::string& componentName);
    template<typename T> T* addComponent();
    template<typename T> T* addComponent(STComponent*);
    void addChild(STEntity* entity);
    STEntity* getChild(int ind);

    void addScript(const std::string& scriptName);

    inline bool hasChildren(){ return m_children.size() > 0; }

    //Attributes
    void addAttribute(const std::string& name, const int& value);
    void addAttribute(const std::string& name, const float& value);
    void addAttribute(const std::string& name, const Vector2<stReal>& value);
    void addAttribute(const std::string& name, const Vector3<stReal>& value);
    void addAttribute(const std::string& name, const Vector4<stReal>& value);

    void setAttribute(const std::string& name, const int& value);
    void setAttribute(const std::string& name, const float& value);
    void setAttribute(const std::string& name, const Vector2<stReal>& value);
    void setAttribute(const std::string& name, const Vector3<stReal>& value);
    void setAttribute(const std::string& name, const Vector4<stReal>& value);

    int getAttributei(const std::string& name) const;
    float getAttributef(const std::string& name) const;
    Vector2<stReal> getAttribute2v(const std::string& name) const;
    Vector3<stReal> getAttribute3v(const std::string& name) const;
    Vector4<stReal> getAttribute4v(const std::string& name) const;

    STEntity* childAtTag(const std::string& tag);
    inline stUint getChildSize(){ return (stUint)m_children.size(); }
    std::vector<std::shared_ptr<STEntity>> getChildren(){ return m_children; }

    inline void setName(const std::string& name){ m_name = name; }
    inline void setTag(const std::string& name){ m_tag = name; }

    inline std::string getTag()const{ return m_tag; }
    inline std::string getName() const{ return m_name; }

    void setVisible(bool value);
    bool isVisible();

    void dispose();

    template<typename T> inline std::vector<T*> getInChildren(){
        auto ret = std::vector<T*>();
        for(auto child : m_children){
            auto entry = child->get<T>();
            if(entry != nullptr){
                ret.push_back(entry);
            }
        }
        return ret;
    }

    std::vector<std::string> getLoadedComponentNames(){
        std::vector<std::string> ret;
        for(auto comp : m_components){
            ret.emplace_back(comp.first);
        }
        return ret;
    }

    const std::map<std::string, STComponent*> &getAllComponents() const;

    /**
     * @brief Returns Component Added to Entity.
     * @tparam T Component Type
     * @return Component Requested
     */
    template<typename T> inline T* get(){
        std::string query;
#if _MSC_VER > 1900
        query = STSerializableUtility::SanitizeStringMSVC(typeid(T).name());
#else
        int status = 0;
        query = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
#endif
        auto it = m_components.find(query);
        if(it != m_components.end()){
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }
    inline Transform* transform(){ return m_transform.get(); }

    void setParent(std::shared_ptr<STEntity> p);
    virtual void update();
    virtual void draw();
    virtual void draw(STGraphics* grphx);
    void draw(Camera* cam);
    virtual void draw(Camera* cam, int drawMode);

    void load(std::ifstream& in);
    void save(std::ofstream& out);
protected:
    Type m_type;
    std::string m_name;
    std::string m_tag;
    stUint numComponents;
    std::shared_ptr<Transform> m_transform;

    std::map<std::string, STComponent*> m_components;
    std::shared_ptr<STEntity> m_parent;
    bool m_visible;
    bool m_isDebug;

    std::map<std::string, std::shared_ptr<STAttribute>> m_attributes;
    std::vector<std::shared_ptr<STEntity>> m_children;
};

template<typename T> T* STEntity::addComponent() {
    auto ret = new T;
    addComponent(typeid(T), ret);
    return ret;
}

template<typename T> T* STEntity::addComponent(STComponent *newComp) {
    auto ret = dynamic_cast<T*>(newComp);
    addComponent(typeid(T), ret);
    return ret;
}


#endif //WAHOO_STENTITY_H
