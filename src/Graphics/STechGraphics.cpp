#include "STechGraphics.h"

STechGraphics::STechGraphics() {

}

STechGraphics::STechGraphics(STechWindow* win){
    WIDTH = (unsigned int)win->getWidth();
    HEIGHT = (unsigned int)win->getHeight();
}

STechGraphics::~STechGraphics() {
    WIDTH = 0;
    HEIGHT = 0;
}