#ifndef WAHOO_STSCRIPTCOMPONENT_H
#define WAHOO_STSCRIPTCOMPONENT_H

#include "STComponent.h"
#include "../STEntity.h"

#if __MINGW32__
#include <sol.hpp>
#else
#include <lua5.1/sol.hpp>
#endif

class STEntity;

class STScriptComponent : public STComponent{
public:
    STScriptComponent(STEntity* entity, const std::string& fileName);

    explicit STScriptComponent(const std::string& fileName);
    void init(STEntity* parent);
    void registerFunction(const std::string& functionName, std::function<void()> newFunction);
    void registerEvent(const std::string& eventName);
    ~STScriptComponent() override;

    void update() override;
    sol::state m_script;
private:
    STGraphicsComponent* getGraphicsComponent();
    void initScript(const std::string& fileName);
    std::string scriptName;
};


#endif //WAHOO_STSCRIPTCOMPONENT_H
