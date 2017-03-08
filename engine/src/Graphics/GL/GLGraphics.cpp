
#if __WINDOWS__
extern "C"{
    #include <ft2build.h>
    #include FT_FREETYPE_H
}
#else
extern "C"{
#include <ft2build.h>
#include FT_FREETYPE_H
};
#endif

#include "GLGraphics.h"

Vector3<stReal> GLGraphics::TextColor = Vector3<stReal>(1.0, 1.0, 1.0);

GLGraphics::GLGraphics() {

}

GLGraphics::GLGraphics(STGame *game) {

    WIDTH = (unsigned int)game->getWidth();
    HEIGHT = (unsigned int)game->getHeight();

    screenQuad = new GLMesh(new STQuad);
    screenShdr = new GLShader("screen");
    Bloom_Threshold = new GLShader("screen", "Bloom_Threshold");
    Bloom_Composite = new GLShader("screen", "Bloom_Composite");
    Motion_Blur = new GLShader("screen","Motion_Blur");
    Tone_Mapping = new GLShader("screen","Tone_Mapping");
    FXAAShader = new GLShader("screen","FXAA");

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

    //Setup Albedo and lit materials for forward rendering
    m_directionalLightMat = new STMaterial(new GLShader("standard"));
    m_pointLightMat = new STMaterial(new GLShader("standard","standard_point_forward"));
    m_albedoMat = new STMaterial(new GLShader("standard","standard_abledo_forward"));
    m_IBLMat = new STMaterial (new GLShader ("standard", "standard_IBL"));
    m_velocityMat =new STMaterial (new GLShader ("Velocity"));


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

void GLGraphics::drawScene(STScene *scene) {
    auto rendScene = scenes[scene->getIndex()];
    if(!rendScene.m_initiated){
        scenes[scene->getIndex()].initSkybox(scene->getSkyboxShader(), scene->getSkyboxName());


        auto w = STGame::RES_WIDTH;
        auto h = STGame::RES_HEIGHT;


        glGenTextures(1, &velocityTexture);

        glBindTexture(GL_TEXTURE_2D, velocityTexture);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RG, GL_FLOAT, NULL);


        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glBindTexture(GL_TEXTURE_2D, 0);

        glGenFramebuffers(1, &bloomThresBuf);
        glGenTextures(1, &bloomThresTex);

        glBindTexture(GL_TEXTURE_2D, bloomThresTex);


        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGB, GL_FLOAT, NULL);


        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glBindTexture(GL_TEXTURE_2D, 0);



        glBindFramebuffer(GL_FRAMEBUFFER, bloomThresBuf);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bloomThresTex, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) std::cout << "Successfully generated bloom buffer." << std::endl;
        GLenum drawBuffers1[] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, drawBuffers1);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);



        glGenFramebuffers(1, &frameBuffer);
        glGenTextures(1, &frameTexBuffer);


        glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);


        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, w);
        glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, h);
        glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 4);


        glGenRenderbuffers(1, &rendBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, rendBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rendBuffer);

        GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
        glDrawBuffers(1, drawBuffers);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
            std::cout << "Successfully generated framebuffer!" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, w, h);

        scenes[scene->getIndex()].m_initiated = true;
    }

    // Bind the frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    auto clearColor = STGraphics::ClearColor;
    glClearColor(0,0,0,1);



    auto actors = scene->getActors();
    auto lights = scene->getLights();

   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, velocityTexture, 0);

    glClear(GL_COLOR_BUFFER_BIT);

    //Depth Pre-Pass
    for(int i =0; i< actors.size(); i++){
        actors[i]->draw(m_velocityMat);
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);


    glClearColor(clearColor.getX(), clearColor.getY(), clearColor.getZ(), clearColor.getZ());
    glClear(GL_COLOR_BUFFER_BIT);

    scenes[scene->getIndex()].drawSkybox(*camera());


    glDisable(GL_BLEND);
    glDepthFunc(GL_EQUAL);
    glDepthMask(GL_TRUE);

    for(int i =0; i < actors.size(); i++){
        for(int j =0; j < lights.size(); j++) {
            actors[i]->setShdrUniform("_CameraPos", camera()->transform()->getTranslate<stReal>());
            actors[i]->setShdrUniform_CubeMap("_WorldCubeMap", scenes[scene->getIndex()].m_skybox);

            actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Color", lights[j]->color);
            actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Intensity", lights[j]->intensity);
            actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Position", lights[j]->transform()->getTranslate<stReal>());
            actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Direction", lights[j]->direction);
            actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Radius", lights[j]->radius);
        }


        actors[i]->draw();

    }


//    //IBL Pass
//    for(int i =0; i < actors.size(); i++) {
//        actors[i]->setShdrUniform("_GlobalAmbient", GlobalAmbient);
//        actors[i]->setShdrUniform_CubeMap("_WorldCubeMap", scenes[scene->getIndex()].m_skybox);
//        actors[i]->setShdrUniform("_CameraPos", camera()->transform()->getTranslate<stReal>());
//        actors[i]->draw(m_IBLMat);
//    }
//
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_ONE,GL_ONE);
//    glDepthFunc(GL_EQUAL);
//
//
//    //Forward Pass
//    for(int i =0; i < actors.size(); i++){
//        for(int j =0; j < lights.size(); j++) {
//
//            actors[i]->setShdrUniform("Light.Color", lights[j]->color);
//            actors[i]->setShdrUniform("Light.Intensity", lights[j]->intensity);
//            actors[i]->setShdrUniform("Light.Position", lights[j]->transform()->getTranslate<stReal>());
//            actors[i]->setShdrUniform("Light.Direction", lights[j]->direction);
//            actors[i]->setShdrUniform("Light.Radius", lights[j]->radius);
//
//            switch(lights[j]->type) {
//                case STLight::DirectionalLight: {
//                    actors[i]->draw(m_directionalLightMat);
//                    break;
//                }
//                case STLight::PointLight: {
//                    actors[i]->draw(m_pointLightMat); // Enabling this draws black cube
//                    break;
//                }
//                case STLight::SpotLight: {
//                    break;
//                }
//            }
//        }
//    }


    glDisable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);



    glBindFramebuffer(GL_FRAMEBUFFER, 0);




    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_CULL_FACE);

    if((m_enabledEffects&BLOOM)>0)Bloom();
    if((m_enabledEffects&MOTION_BLUR)>0)MotionBlur();
    if((m_enabledEffects&TONE_MAPPING)>0)ToneMapping();
    if((m_enabledEffects&FXAA)>0)RenderScreenWithShader(FXAAShader);


    glClearColor(1.0, 1.0, 1.0, 1.0);

    screenShdr->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    screenQuad->draw();
    screenShdr->unbind();

}



void GLGraphics::Bloom(){



    glBindFramebuffer(GL_FRAMEBUFFER, bloomThresBuf);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bloomThresTex, 0);



    Bloom_Threshold->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    screenQuad->draw();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D,bloomThresTex);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);


    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);



    Bloom_Composite->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bloomThresTex);
    screenQuad->draw();
    Bloom_Composite->unbind();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}


void GLGraphics::MotionBlur(){



    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);



    Motion_Blur->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, velocityTexture);
    screenQuad->draw();
    Motion_Blur->unbind();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);




}


void GLGraphics::ToneMapping() {

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);


    Tone_Mapping->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    screenQuad->draw();
    Tone_Mapping->unbind();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);




}


void GLGraphics::RenderScreenWithShader(const std::string& shaderName) {

    GLShader* tempShader = new GLShader("screen",shaderName);

    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);


    tempShader->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    screenQuad->draw();
    tempShader->unbind();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    delete tempShader;
}

void GLGraphics::RenderScreenWithShader(GLShader* shader) {


    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);


    shader->bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    screenQuad->draw();
    shader->unbind();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void GLGraphics::drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize) {
    glEnable(GL_BLEND);
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

void GLGraphics::initScene(stUint index) {
    scenes.insert(std::pair<stUint, GLRenderScene>(index, GLRenderScene()));
}

