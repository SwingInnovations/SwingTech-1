#include "STGraphics.h"

STGraphics::STGraphics() {

}

STGraphics::STGraphics(STGame * win){
    WIDTH = (unsigned int)win->getWidth();
    HEIGHT = (unsigned int)win->getHeight();
}

STGraphics::~STGraphics() {
    WIDTH = 0;
    HEIGHT = 0;
}