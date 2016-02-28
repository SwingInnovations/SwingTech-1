#include "STGraphics.h"

STGraphics::STGraphics() {
    m_XUp = false;
}

STGraphics::STGraphics(STGame * win){
    WIDTH = (unsigned int)win->getWidth();
    HEIGHT = (unsigned int)win->getHeight();
    m_XUp = false;
}

STGraphics::~STGraphics() {
    WIDTH = 0;
    HEIGHT = 0;
}