#include "STRenderer.h"

STRenderer::STRenderer(STGame *win) {
    m_windowSize = Vector2D( win->getWidth(), win->getHeight() );
}

void STRenderer::enabledEffects(const stUint effects) {

}

void STRenderer::disableEffects(const stUint effects) {

}
