#include "STMeshComponent.h"
#include "../../Graphics/STGraphics.h"
#include "../../Graphics/GL/GLMesh.h"
#include "../../Graphics/GL/GLSkinnedMesh.h"

STMeshComponent::STMeshComponent() {

}


STMeshComponent::STMeshComponent(STMesh_Structure structure) {
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        if(structure.m_hasBones){
            m_Mesh = std::make_shared<GLSkinnedMesh>(structure);
            m_Mesh->setMeshStructure(structure);
            return;
        }
        m_Mesh = std::make_shared<GLMesh>(structure);
        m_Mesh->setMeshStructure(structure);
    }
}

STMeshComponent::STMeshComponent(Shape& shape) {

}

STMeshComponent::STMeshComponent(STQuad *quad) {
//    if(STGraphics::RENDERER == STGraphics::OPENGL){
//        m_mesh = new GLMesh(quad);
//    }
}

STMeshComponent::STMeshComponent(STRect *rect) {
//    if(STGraphics::RENDERER == STGraphics::OPENGL){
//        m_mesh = new GLMesh(rect);
//    }
}

STMeshComponent::STMeshComponent(STCube* cube) {
//    if(STGraphics::RENDERER == STGraphics::OPENGL) m_mesh = new GLMesh(cube);
}

STMeshComponent::STMeshComponent(float *vert, int vSize, float *tex, int tSize, int *ind, int indSize) {
//    if(STGraphics::RENDERER == STGraphics::OPENGL){
//        m_mesh = new GLMesh(vert, vSize, tex, tSize, ind, indSize);
//    }
}

STMeshComponent::~STMeshComponent() {
    m_Mesh.reset();
}

void STMeshComponent::update() {

}

STMesh *STMeshComponent::getMesh() const {
    return m_Mesh.get();
}

void STMeshComponent::dispose() {
   m_Mesh.reset();
}

void STMeshComponent::save(std::ofstream &out) {
    m_Mesh->save(out);
}

void STMeshComponent::load(std::ifstream &in) {
    bool hasAnimation = false;
    in.read((char*)&hasAnimation, sizeof(bool));
    if(STGraphics::RENDERER == STGraphics::OPENGL){
        if(hasAnimation){
            m_Mesh = std::make_shared<GLSkinnedMesh>();
            m_Mesh->load(in, hasAnimation);
        }else{
            m_Mesh = std::make_shared<GLMesh>();
            m_Mesh->load(in, hasAnimation);
        }
    }
}

REGISTER_COMPONENT(STMeshComponent)


