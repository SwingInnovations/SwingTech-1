#include "GLRenderer.h"

GLRenderer::GLRenderer(STGame *win) : STRenderer(win) {

}

GLRenderer::GLRenderProxy::GLRenderProxy(STEntity *entity) : IRenderProxy(entity) {
    m_entity = (void*)entity;
}

void GLRenderer::GLRenderProxy::draw(STRenderer *renderer) {

}
