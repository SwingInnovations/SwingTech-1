#include "STEntry.h"

STEntry::STEntry() {
    this->m_defaultText = "Enter Text Here.";
    this->m_inFocus = false;
}

void STEntry::update(STGame *window) {
    if(m_inFocus){
        m_text += window->getInput()->getInputCharacter();
    }
}

void STEntry::draw(STGraphics *g) {
    if(m_visible){
        if(m_text != ""){ /*Draw text*/ }else{
            //Draw Default Text
        }
    }
}


