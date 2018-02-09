#include "STPanel.h"
#include "../GL/GLShader.h"

STPanel::STPanel(int x, int y, int width, int height) {
    m_transform = std::make_shared<Transform>();
    m_transform->setEntity(shared_from_this());
    m_position.set(x, y);
    m_baseColor.set(Vector4<stReal>(0.24f, 0.24f, 0.24f, 1.0f));
    int bY = abs( y - STGame::RES_HEIGHT) - height;
    //addComponent(typeid(STMeshComponent), new STMeshComponent(new STRect(x, y, width, height)));
    Shader* shdr;
    if(STGraphics::RENDERER == STGraphics::OPENGL) shdr  = new GLShader("shdr/panel");
    else return;
    //addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(shdr)));
    //addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height, STGraphics::YUp));

    auto grphx = get<STRendererComponent>();
    grphx->addShdrUniform("baseColor", m_baseColor.color);
}

void STPanel::draw(STGraphics *grphx) {
    auto gfx = get<STRendererComponent>();
    auto mesh = get<STMeshComponent>();

    grphx->enableBlend();
    gfx->draw();
    gfx->setShdrUniform("projection", grphx->getOrthographicProjection());
    gfx->setShdrUniform("model", m_transform->getModel());
    gfx->setShdrUniform("baseColor", m_baseColor.color);
    mesh->draw();
    grphx->disableBlend();
}

void STPanel::reset(int x, int y, stReal w, stReal h) {
    auto rect = get<STRectBoundsComponent>();
    if(rect != nullptr){
        rect->reset(x, y, w, h);
        m_transform->setTranslateX(x);
        m_transform->setTranslateY(y);
    }
}
