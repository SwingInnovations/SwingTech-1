#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include <utility>
#include <fstream>

#include "../../../include/sol.hpp"
#include "../../Application/STGame.h"

class STEntity;
/**
 * Parent of componenet can always be referred to by accessing the parent.
 * Game can be accessed via the STGame Singleton
 */
class STComponent {
public:
    virtual void init(std::shared_ptr<STEntity>& newParent){this->m_entity = newParent;}      //This will actually initialize anything dependent on the m_entity pointer.
    virtual void ReInitFromSave(std::shared_ptr<STEntity> parent ){ /*Reimplement this for every component as mandatory*/;}
    /**
     * Initializes stuff
     */
    virtual void initScriptingFunctions(sol::state& m_script){;}
    virtual void update() = 0;
    virtual void draw(){ }
    /**
     * @brief Independently called to clear contents of component.
     */
    virtual void dispose(){}
    virtual ~STComponent(){}

    virtual void save(std::ofstream& out) = 0;
    virtual void load(std::ifstream& in) = 0;

    inline void setParent(std::shared_ptr<STEntity> parent){ this->m_entity = std::move(parent); }
    STEntity* getParent(){ return this->m_entity.get(); }
protected:
    std::shared_ptr<STEntity> m_entity;

};

class STComponentFactory{
public:
    virtual std::shared_ptr<STComponent> create() = 0;
};

class STComponentObject{
public:
    static void registerClass(const std::string& name, STComponentFactory* factory){
        m_registeredTypes[name] = factory;
    }

    static std::shared_ptr<STComponent> create(const std::string& name){
        auto it = m_registeredTypes.find(name);
        if(it != m_registeredTypes.end()){
            return m_registeredTypes[name]->create();
        }
        return nullptr;
    }

    static std::map<std::string, STComponentFactory*> m_registeredTypes;
};

#define REGISTER_COMPONENT(CLASS) \
    class CLASS##Factory : public STComponentFactory {\
        public: \
            CLASS##Factory()\
                { \
                    STComponentObject::registerClass(#CLASS, this); \
                 } \
            virtual std::shared_ptr<STComponent> create(){\
                return std::make_shared<CLASS>(); \
            } \
        }; \
        static CLASS##Factory global_##CLASS##Factory;

#endif //WAHOO_STCOMPONENT_H
