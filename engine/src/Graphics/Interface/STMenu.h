#ifndef SWINGTECH1_STMENU_H
#define SWINGTECH1_STMENU_H

#include <c++/functional>
#include <string>

class STMenuEntry{
public:
    STMenuEntry();
    STMenuEntry(const std::string& name, std::function function);
private:
    std::string name;
    std::function function;
};

class STMenu {

};


#endif //SWINGTECH1_STMENU_H
