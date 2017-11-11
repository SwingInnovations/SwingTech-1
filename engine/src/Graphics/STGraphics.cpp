#include "STGraphics.h"
#include "../Application/STGame.h"

Vector4<stReal> STGraphics::ClearColor = Vector4<stReal>(0.0f, 0.0f, 0.0f, 1.0f);

Vector3<stReal> STGraphics::GlobalAmbient = Vector3<stReal>(.4f, .4f, .4f);
int STGraphics::RENDERER = STGraphics::OPENGL;
bool STGraphics::YUp = false;

STGraphics::STGraphics() {
    m_activeCameraIndex = 0;
    setRenderMode(RenderMode::FORWARD);
}

STGraphics::STGraphics(STGame * win){
    WIDTH = (unsigned int)win->getWidth();
    HEIGHT = (unsigned int)win->getHeight();
    m_activeCameraIndex = 0;
    setRenderMode(RenderMode::FORWARD);
}

STGraphics::~STGraphics() {
    WIDTH = 0;
    HEIGHT = 0;
}

void STGraphics::setCurrentCamera(stUint cameraIndex) {
    m_activeCameraIndex = cameraIndex;
}
