#include "STPanel.h"

STPanel::STPanel(int x, int y, int width, int height) {
    m_position.set(x, y);
    m_backgroundColor.set(Vector3<stReal>(0.5f, 0.5f, 0.5f));
    m_foregroundColor.set(Vector3<stReal>(0.5f, 0.5f, 0.5f));
    int bY = abs( y - STGame::RES_HEIGHT) - height;
    addComponent(typeid(STMeshComponent), new STMeshComponent(new STRect(x, y, width, height)));
    Shader* shdr;
    if(STGraphics::RENDERER == STGraphics::OPENGL) shdr  = new GLShader("shdr/panel");
    else return;
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(shdr)));
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height, STGraphics::YUp));

    auto grphx = get<STGraphicsComponent>();
    grphx->addShdrUniform("foregoundColor", m_foregroundColor.color);
    grphx->addShdrUniform("backgroundColor", m_backgroundColor.color);
}

void STPanel::draw(STGraphics *grphx) {
    auto gfx = get<STGraphicsComponent>();
    auto mesh = get<STMeshComponent>();



//    gfx->setShdrUniform("foregroundColor", Vector3<stReal>(0.5f, 0.5f, 0.5f));
//    gfx->setShdrUniform("backgroundColor", m_backgroundColor.color);
//    gfx->draw();
    //TODO this is temporary, should remove after optimizations. 
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        auto mat = grphx->getOrthographicProjection();
        ((GLShader*)gfx->shdr())->bind();
        ((GLShader*)gfx->shdr())->update("projection", mat);
        ((GLShader*)gfx->shdr())->update("foregroundColor", m_backgroundColor.color.toVector3());
    }
    mesh->draw();
}
