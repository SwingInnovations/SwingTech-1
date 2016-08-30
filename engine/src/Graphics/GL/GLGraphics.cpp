extern "C"{
    #include <ft2build.h>
    #include FT_FREETYPE_H
}

#include "GLGraphics.h"

Vector3<stReal> GLGraphics::TextColor = Vector3<stReal>(1.0, 1.0, 1.0);

GLRenderPass::GLRenderPass() {

}

GLRenderPass::GLRenderPass(unsigned int x, unsigned int y) {
    width = x;
    height = y;
    mesh = new STMeshComponent(new STQuad);
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

void GLRenderPass::unBind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    postShader->bind();
    glBindTexture(GL_TEXTURE_2D, texBuffer);
    mesh->draw();
}

void GLRenderPass::setScene(STSceneManager* sceneManager){
    entities = sceneManager->getEntities();
    lights = sceneManager->getLights();

    skyboxMesh = new GLMesh(new STCube(1000));
    skyBox = GLTexture::loadCubemapTexture(sceneManager->getSkyboxName().c_str());
    skyboxShdr = new GLShader(sceneManager->getSkyboxShader().c_str());
}

void GLRenderPass::setScene(STScene *scene) {
    actors = scene->getActors();
    lights = scene->getLights();

    skyboxMesh = new GLMesh(new STCube(1000));
    skyBox = GLTexture::loadCubemapTexture(scene->getSkyboxName().c_str());
    skyboxShdr = new GLShader(scene->getSkyboxShader().c_str());
}

void GLRenderPass::setEntities(std::vector<STEntity *> _entities) {
    entities = _entities;
}

void GLRenderPass::setLights(std::vector<STLight *> _lights) {
    lights = _lights;
}

void GLRenderPass::drawSkybox(GLGraphics *g) {
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    skyboxShdr->bind();
    skyboxShdr->update(*g->camera());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox);
    skyboxMesh->draw();
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
}

void GLRenderPass::draw(GLGraphics *g) {
    bind();
    drawSkybox(g);
    if(entities.size() >= 1){
        for(auto ent : entities){
            ent->draw(g);
        }
    }

    if(actors.size() >= 1){
        for(auto act : actors){
            act->draw();
        }
    }

    unBind();
}



GLGraphics::GLGraphics() {

}

GLGraphics::GLGraphics(STGame *game) {
    WIDTH = (unsigned int)game->getWidth();
    HEIGHT = (unsigned int)game->getHeight();



    FT_Library ft;
    if(FT_Init_FreeType(&ft)){ std::cout << "foo" << std::endl; }else{ std::cout << "Successfully loaded FreeType!" << std::endl; }

    FT_Face face;
    if(FT_New_Face(ft, "fonts/arial.ttf", 0, &face)){ std::cout << "Something went wrong" << std::endl; }
    FT_Set_Pixel_Sizes(face, 0, 128);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte c = 0; c < 128; c++){
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "Failed to load Character" << std::endl;
            continue;
        }
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RED,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = { texture,
                                Vector2<int>(face->glyph->bitmap.width,
                                             face->glyph->bitmap.rows),
                                Vector2<int>(face->glyph->bitmap_left,
                                             face->glyph->bitmap_top),
                                (GLuint)face->glyph->advance.x };
        characters.insert(std::pair<GLchar, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    textShader = new GLShader("text");
    orthoProjection.initOrthographicProjection(0, WIDTH, HEIGHT, 0, 0, 1000.0f);

    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4* sizeof(GL_FLOAT), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLGraphics::setShader(int ind, Shader *shdr) {
    if(ind < renderPass.size()){
        renderPass[ind]->postShader = (GLShader*)shdr;
    }
}

void GLGraphics::addRenderPass(STSceneManager *scene, GLShader *shdr) {
    renderPass.push_back(new GLRenderPass(WIDTH, HEIGHT, shdr));
    auto rend = renderPass.back();
    rend->setScene(scene);
}

void GLGraphics::drawScene(STSceneManager *scene) {
    for(auto rendPass : renderPass){
        rendPass->draw(this);
    }
}

void GLGraphics::drawScene(STScene *scene) {
    for(auto rendPass : renderPass){
        rendPass->draw(this);
    }
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize) {
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", GLGraphics::TextColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string &text, stReal fontSize, Vector4<stReal> *color) {
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", *color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string &text, stReal fontSize, stReal value) {
    std::string string = text;
    string = string.replace(string.find("%d"), sizeof(std::to_string(value))-1, std::to_string(value));

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", GLGraphics::TextColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = string.begin(); c != string.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string &text, stReal fontSize, stReal v1, stReal v2) {
    std::string string = text;
    auto sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(v1));
    }
    sPos = string.find("%");
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(v2));
    }

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", GLGraphics::TextColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = string.begin(); c != string.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string &text, stReal fontSize, Vector2<stReal> vector) {
    std::string string = text;
    auto sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(vector.getX()));
    }
    sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(vector.getY()));
    }

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", GLGraphics::TextColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = string.begin(); c != string.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string &text, stReal fontSize, stReal v1, stReal v2,
                          stReal v3) {
    std::string string = text;
    auto sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(v1));
    }
    sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(v2));
    }
    sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(v3));
    }

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", GLGraphics::TextColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = string.begin(); c != string.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string &text, stReal fontSize, Vector3<stReal> vector) {
    std::string string = text;
    std::cout << "Type: " << typeid(5.0f).name() << std::endl;
    auto sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(vector.getX()));
    }
    sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(vector.getY()));
    }
    sPos = string.find('%');
    if(string.at(sPos+1) == 'd'){
        string.erase(sPos, 2);
        string.insert(sPos, std::to_string(vector.getZ()));
    }


    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", GLGraphics::TextColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = string.begin(); c != string.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string &text, stReal fontSize, std::string &msg) {
    std::string string = text;
    string = string.replace(string.find("%s"), msg.length()-1, msg);

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader->bind();
    textShader->update("projection", orthoProjection);
    textShader->update("textColor", GLGraphics::TextColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(textVAO);

    GLfloat x = pos.getX();
    GLfloat y = pos.getY();

    fontSize /= 128.0f;

    std::string::const_iterator c;
    for(c = string.begin(); c != string.end(); c++){
        Character ch = characters[*c];

        GLfloat xPos = x + ch.bearing.getX() * fontSize;
        GLfloat yPos = y - (ch.size.getY() - ch.bearing.getY()) * fontSize;

        GLfloat w = ch.size.getX() * fontSize;
        GLfloat h = ch.size.getY() * fontSize;

        GLfloat verts[6][4] = {
                {xPos, yPos, 0.0, 1.0},
                {xPos + w, yPos, 1.0, 1.0 },
                {xPos, yPos+h,  0.0, 0.0},

                {xPos, yPos+h,  0.0, 0.0},
                {xPos + w, yPos + h, 1.0, 0.0},
                {xPos + w, yPos, 1.0, 1.0 }
        };
        glBindTexture(GL_TEXTURE_2D, ch.texID);
        glBindBuffer(GL_ARRAY_BUFFER, textVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        x+=( ch.Advance >> 6 ) * fontSize;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

std::string GLGraphics::getVendor() {
    return reinterpret_cast<char const* >( glGetString(GL_VENDOR) );
}

