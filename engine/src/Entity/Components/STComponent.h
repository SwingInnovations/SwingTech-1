#ifndef WAHOO_STCOMPONENT_H
#define WAHOO_STCOMPONENT_H

#include <utility>

#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>

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

    inline void setParent(std::shared_ptr<STEntity> parent){ this->m_entity = std::move(parent); }
    STEntity* getParent(){ return this->m_entity.get(); }

    template <class Archive> void serialize(Archive& ar){ ; }
protected:
    std::shared_ptr<STEntity> m_entity;
};


#endif //WAHOO_STCOMPONENT_H
