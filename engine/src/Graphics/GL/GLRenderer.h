#ifndef SWINGTECH1_GLRENDERER_H
#define SWINGTECH1_GLRENDERER_H

#include "../STRenderer.h"

/**
 *
 */
class GLRenderer : STRenderer{
public:
    class GLRenderProxy : public STRenderer::IRenderProxy{
    public:
        GLRenderProxy(STEntity *entity);
        void draw(STRenderer* renderer) override;

    };
    GLRenderer(STGame *win);

private:

};


#endif //SWINGTECH1_GLRENDERER_H
