#include "STMeshComponent.h"
#include "../../Graphics/STGraphics.h"
#include "../../Graphics/GL/GLMesh.h"

STMeshComponent::STMeshComponent(const std::string &fileName, int type) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        m_mesh = new GLMesh(fileName, type);
    }
}

STMeshComponent::STMeshComponent(const std::string &fileName) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        m_mesh = new GLMesh(fileName);
    }
}

STMeshComponent::STMeshComponent(const std::string &fileName, int type, Vector2<stInt> bounds) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        m_mesh = new GLMesh(fileName, type, bounds);
    }
}

STMeshComponent::STMeshComponent(Shape& shape) {

}

STMeshComponent::STMeshComponent(STQuad *quad) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        m_mesh = new GLMesh(quad);
    }
}

STMeshComponent::STMeshComponent(STRect *rect) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        m_mesh = new GLMesh(rect);
    }
}

STMeshComponent::STMeshComponent(STCube* cube) {
    if(STGraphics::RENDERER == STGraphics::OPENGL) m_mesh = new GLMesh(cube);
}

STMeshComponent::STMeshComponent(float *vert, int vSize, float *tex, int tSize, int *ind, int indSize) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        m_mesh = new GLMesh(vert, vSize, tex, tSize, ind, indSize);
    }
}

STMeshComponent::~STMeshComponent() {
    delete m_mesh;
}

void STMeshComponent::update() {

}



