#include "STMenu.h"

STMenuEntry::STMenuEntry() {
    name = "";
    function = nullptr;
}

STMenuEntry::STMenuEntry(const std::string &name, std::function function) {
    this->name = name;
    this->function = function;
}
