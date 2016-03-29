#include "STGraphics.h"

Vector4<stReal> STGraphics::ClearColor = Vector4<stReal>(0.0f, 0.0f, 0.0f, 1.0f);

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