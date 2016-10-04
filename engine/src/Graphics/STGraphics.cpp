#include "STGraphics.h"

Vector4<stReal> STGraphics::ClearColor = Vector4<stReal>(0.0f, 0.0f, 0.0f, 1.0f);

Vector3<stReal> STGraphics::GlobalAmbient = Vector3<stReal>(.4f, .4f, .4f);
int STGraphics::RENDERER = STGraphics::OPENGL;
bool STGraphics::YUp = false;

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