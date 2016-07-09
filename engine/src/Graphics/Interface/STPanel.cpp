#include "STPanel.h"

STPanel::STPanel(int x, int y, int width, int height) {
    m_position.set(x, y);
    m_foregroundColor.set(BLUE);
    m_backgroundColor.set(RED);
    int bY = abs( y - STGame::RES_HEIGHT) - height;
    addComponent(typeid(STMeshComponent), new STMeshComponent(new STRect(x, y, width, height)));
    addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(new STMaterial(new Shader("shdr/panel"))));
    addComponent(typeid(STRectBoundsComponent), new STRectBoundsComponent(x, y, width, height, STGraphics::YUp));

    auto grphx = get<STGraphicsComponent>();
    grphx->addShdrUniform("foregoundColor", m_foregroundColor.color);
    grphx->addShdrUniform("backgroundColor", m_backgroundColor.color);
}

void STPanel::draw(STGraphics *grphx) {
    auto gfx = get<STGraphicsComponent>();
    auto mesh = get<STMeshComponent>();

    gfx->draw();
    gfx->setShdrUniform("foregroundColor", m_foregroundColor.color);
    gfx->setShdrUniform("backgroundColor", m_backgroundColor.color);
    mesh->draw();
}
