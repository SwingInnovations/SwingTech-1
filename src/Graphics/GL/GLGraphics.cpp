#include "GLGraphics.h"

GLRenderPass::GLRenderPass() {

}

GLRenderPass::GLRenderPass(unsigned int x, unsigned int y) {
    width = x;
    height = y;
    mesh = new STMeshComponent(new SWRect(0, 0, 2, 2));
    postShader = new GLShader("Shader/screen", "Shader/default");

    glGenFramebuffers(1, &frameBuffer);
    glGenTextures(1, &texBuffer);

    glBindTexture(GL_TEXTURE_2D, texBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, width);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, height);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 4);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texBuffer, 0);

    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);


    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
        std::cout << "Successfully generated Framebuffer" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
}

GLRenderPass::GLRenderPass(unsigned int x, unsigned int y, GLShader* shdr) {
    width = x;
    height = y;
    mesh = new STMeshComponent(new STQuad());
    postShader = shdr;

    glGenFramebuffers(1, &frameBuffer);
    glGenTextures(1, &texBuffer);

    glBindTexture(GL_TEXTURE_2D, texBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, width);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, height);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 4);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texBuffer, 0);

    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);


    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "Unsuccessfully generated Framebuffer" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLRenderPass::GLRenderPass(unsigned int x, unsigned int y, std::string &name) {

}

GLRenderPass::~GLRenderPass() {

}

void GLRenderPass::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    Vector4<stReal> clearColor = STGraphics::ClearColor;
    glClearColor(clearColor.getX(), clearColor.getY(), clearColor.getZ(), clearColor.getW());
}

void GLRenderPass::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    postShader->bind();
    glBindTexture(GL_TEXTURE_2D, texBuffer);
    mesh->draw();
}

void GLRenderPass::setEntities(std::vector<STEntity *> _entities) {
    entities = _entities;
}

void GLRenderPass::setLights(std::vector<STLight *> _lights) {
    lights = _lights;
}

void GLRenderPass::draw(GLGraphics *g) {
    bind();
    if(entities.size() >= 1){
        for(auto ent : entities){
            ent->draw(g->camera());
        }
    }
    unbind();
}

GLGraphics::GLGraphics() {

}

GLGraphics::GLGraphics(STGame *game) {
    WIDTH = (unsigned int)game->getWidth();
    HEIGHT = (unsigned int)game->getHeight();
}

void GLGraphics::setShader(int ind, Shader *shdr) {
    if(ind < renderPass.size()){
        renderPass[ind]->postShader = (GLShader*)shdr;
    }
}

void GLGraphics::addRenderPass(STSceneManager *scene, GLShader *shdr) {
    renderPass.push_back(new GLRenderPass(WIDTH, HEIGHT, shdr));
    auto rend = renderPass.back();
    rend->setEntities(scene->getEntities());
}

void GLGraphics::drawScene(STSceneManager *scene) {
    for(auto rendPass : renderPass){
        rendPass->draw(this);
    }
}