
#if __MINGW32__
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
    stUint width = (stUint)game->getWidth();
    stUint height = (stUint)game->getHeight();
    init(width, height);
}

void GLGraphics::init(stUint w, stUint h) {
    WIDTH = w;
    HEIGHT = h;

    m_shadowRes = 1024;

    screenQuad = new GLMesh(new STQuad);
    screenShdr = new GLShader("screen");
    Bloom_Threshold = new GLShader("screen", "Bloom_Threshold");
    Bloom_Composite = new GLShader("screen", "Bloom_Composite");
    Motion_Blur = new GLShader("screen", "Motion_Blur");
    Tone_Mapping = new GLShader("screen", "Tone_Mapping");
    FXAAShader = new GLShader("screen", "FXAA");
    Deff_LightPassShdr = new GLShader("screen", "deff_LightPassPBR");

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Failed to load Freetype!" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face)) { std::cout << "Something went wrong" << std::endl; }
    FT_Set_Pixel_Sizes(face, 0, 128);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
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

        Character character = {texture,
                               Vector2<int>(face->glyph->bitmap.width,
                                            face->glyph->bitmap.rows),
                               Vector2<int>(face->glyph->bitmap_left,
                                            face->glyph->bitmap_top),
                               (GLuint) face->glyph->advance.x};
        characters.insert(std::pair<GLchar, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    textShader = new GLShader("text");
    orthoProjection.initOrthographicProjection(0, WIDTH, HEIGHT, 0, 0, 1000.0f);

    //Setup Albedo and lit materials for forward rendering
    m_directionalLightMat = new STMaterial(new GLShader("standard"));
    m_pointLightMat = new STMaterial(new GLShader("standard", "standard_point_forward"));
    m_albedoMat = new STMaterial(new GLShader("standard", "standard_abledo_forward"));
    m_IBLMat = new STMaterial(new GLShader("standard", "standard_IBL"));
    m_velocityMat = new STMaterial(new GLShader("Velocity"));
    m_GBufferOverrideMat = new STMaterial(new GLShader("standard", "deff_geomPass"));

    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, w);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, h);
    glFramebufferParameteri(GL_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, 4);

    glGenTextures(1, &frameTexBuffer);
    glBindTexture(GL_TEXTURE_2D, frameTexBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &rendBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, rendBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rendBuffer);

    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Failed to create FrameBuffer" << std::endl;
    }else{
        std::cout << "Successfully Created Frame buffer" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenTextures(1, &velocityTexture);
    glBindTexture(GL_TEXTURE_2D, velocityTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RG, GL_FLOAT, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &bloomThresBuf);
    glBindFramebuffer(GL_FRAMEBUFFER, bloomThresBuf);
    glGenTextures(1, &bloomThresTex);

    glBindTexture(GL_TEXTURE_2D, bloomThresTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bloomThresTex, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Failed to generate Bloom Buffer" << std::endl;
    GLenum drawBuffers1[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers1);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

    glGenTextures(1, &gColorSpec);
    glBindTexture(GL_TEXTURE_2D, gColorSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColorSpec, 0);;

    glGenTextures(1, &gMRA);
    glBindTexture(GL_TEXTURE_2D, gMRA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gMRA, 0);

    glGenTextures(1, &gTangent);
    glBindTexture(GL_TEXTURE_2D, gTangent);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, gTangent, 0);

    GLuint glAttachments[5] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4};
    glDrawBuffers(5, glAttachments);

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cerr << "Deffered Depth Buffer not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, w, h);
}

void GLGraphics::drawScene(STScene *scene) {
    auto rendScene = (GLRenderScene*)scene->getRenderScene();
    if(!scene->getRenderScene()->m_initiated) {
        rendScene->initSkybox(scene->getSkyboxShader(), scene->getSkyboxName());

        auto w = STGame::RES_WIDTH;
        auto h = STGame::RES_HEIGHT;

        //region Enable Shadows.
        if (m_shadows) {
            stUint lightInd = 0;
            auto lights = scene->getLights();
            glGenTextures(1, &shadowArray);
            glBindTexture(GL_TEXTURE_2D_ARRAY, shadowArray);
            glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_DEPTH_COMPONENT, m_shadowRes, m_shadowRes, (stInt)lights.size(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

            for (stInt i = 0, S = lights.size(); i < S; i++) {
                auto lightProperties = lights[i]->get<STLightComponent>()->getProperties();
                if(lightProperties->useShadow == 0) lightProperties->useShadow = 1;
                auto shadowProperties = lights[i]->get<STShadowComponent>()->getProperties();
                if ((lights[i]->get<STLightComponent>()->getType() == STLightComponent::DIRECTIONAL_LIGHT ||
                        lights[i]->get<STLightComponent>()->getType() == STLightComponent::SPOT_LIGHT) && lightProperties->useShadow == 1) {
                    shadowProperties->shadowIndex = lightInd++;
                    glGenFramebuffers(1, &shadowProperties->shadowFrameBuffer[0]);
                    glBindFramebuffer(GL_FRAMEBUFFER, shadowProperties->shadowFrameBuffer[0]);
                    glGenTextures(1, &shadowProperties->shadowMapID[0]);
                    glBindTexture(GL_TEXTURE_2D, shadowProperties->shadowMapID[0]);
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowRes, m_shadowRes, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                                 NULL);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                                           shadowProperties->shadowMapID[0], 0);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glBindTexture(GL_TEXTURE_2D, 0);

                    glDrawBuffer(GL_NONE);
                    glReadBuffer(GL_NONE);
                    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
                        std::cerr << "Error: Failed to generate Framebuffer for shadow on Light: " + i << std::endl;
                    }
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);

                    lights[i]->projections[0] = Matrix4f::LookAt(lights[i]->transform()->getTranslate(),
                                                                 lights[i]->get<STLightComponent>()->getProperties()->direction,
                                                                 Vector3<stReal>(0, 1, 0));
                    lights[i]->addComponent(typeid(STGraphicsComponent), new STGraphicsComponent(
                            new STMaterial(new GLShader("direct_shadows"))));
                } else if(lights[i]->get<STLightComponent>()->getType() == STLightComponent::POINT_LIGHT){
                    auto pos = lights[i]->transform()->getTranslate();
                    lights[i]->projections[0] = Matrix4f::LookAt(pos, pos - Vector3<stReal>(1.0f, 0.0f, 0.0f),
                                                                 Vector3<stReal>(0.0, -1.0f, 0.0));    //Right
                    lights[i]->projections[1] = Matrix4f::LookAt(pos, pos - Vector3<stReal>(-1.0f, .0, 0.0),
                                                                 Vector3<stReal>(0.0, -1.0f, 0.0));    //Left
                    lights[i]->projections[2] = Matrix4f::LookAt(pos, pos - Vector3<stReal>(0.0, 1.0, 0.0),
                                                                 Vector3<stReal>(0.0, 0.0, 1.0));    //Top
                    lights[i]->projections[3] = Matrix4f::LookAt(pos, pos - Vector3<stReal>(0.0, -1.0f, 0.0),
                                                                 Vector3<stReal>(0.0, 0.0, 1.0));    //Bottom
                    lights[i]->projections[4] = Matrix4f::LookAt(pos, pos - Vector3<stReal>(0.0, 0.0, 1.0),
                                                                 Vector3<stReal>(0.0, -1.0f, 0.0));    //Near
                    lights[i]->projections[5] = Matrix4f::LookAt(pos, pos - Vector3<stReal>(0.0, 0.0, -1.0f),
                                                                 Vector3<stReal>(0.0, -1.0f, 0.0));    //Far
                    lights[i]->addComponent(typeid(STGraphicsComponent),
                                            new STGraphicsComponent(new GLShader("spotLight_shadows")));
                    for (stUint j = 0; j < 6; j++) {
                        glGenFramebuffers(1, &lights[i]->shadowFrameBuffer[j]);
                        glGenTextures(1, &lights[i]->shadowMapID[j]);
                        glBindTexture(GL_TEXTURE_2D, lights[i]->shadowMapID[j]);
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_shadowRes, m_shadowRes, 0,
                                     GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                        glBindFramebuffer(GL_FRAMEBUFFER, lights[i]->shadowFrameBuffer[j]);
                        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                                               lights[i]->shadowMapID[j], 0);
                        glDrawBuffer(GL_NONE);
                        glReadBuffer(GL_NONE);
                        glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    }
                }
            }
        }

        rendScene->m_initiated = true;
    }// endregion

    auto actors = scene->getActors();
    auto lights = scene->getLights();
    //INITIALIZE the shadows;
    if(m_shadows) {
        glViewport(0, 0, m_shadowRes, m_shadowRes);
        auto ortho = Matrix4f().initOrthographicProjection(-15.f, 15.f, -15.f, 15.f, 1.f, 15.f);
        auto persp = Matrix4f().initPerpectiveProjection(45, 10, 10, 1.f, 10);
        for(stUint i = 0; i < lights.size(); i++){
            auto shadowProps = lights[i]->get<STShadowComponent>()->getProperties();
            auto lightProps = lights[i]->get<STLightComponent>()->getProperties();
            if((lights[i]->get<STLightComponent>()->getType() == STLightComponent::DIRECTIONAL_LIGHT ||
                    lights[i]->get<STLightComponent>()->getType() == STLightComponent::SPOT_LIGHT) && lightProps->useShadow == 1) {
                shadowProps->projections[0] = ortho * lights[i]->get<STLightComponent>()->getLookAt();
                auto data = new GLfloat[m_shadowRes*m_shadowRes];
                glBindFramebuffer(GL_FRAMEBUFFER, shadowProps->shadowFrameBuffer[0]);
                glClear(GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                for (auto &actor : actors) {
                    actor->setShdrUniform("lightSpaceMatrix", shadowProps->projections[0]);
                    actor->draw(lights[i]->get<STGraphicsComponent>()->getMaterial());
                }
                glBindTexture(GL_TEXTURE_2D, shadowProps->shadowMapID[0]);
                glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, data);
                glBindTexture(GL_TEXTURE_2D, 0);

                glBindTexture(GL_TEXTURE_2D_ARRAY, shadowArray);
                glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, (int)shadowProps->shadowIndex, m_shadowRes, m_shadowRes, 1, GL_DEPTH_COMPONENT, GL_FLOAT, data);
                glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
                glDisable(GL_CULL_FACE);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                delete[] data;
            }else if(lights[i]->get<STLightComponent>()->getType() == STLightComponent::POINT_LIGHT){
                for(stUint j = 0; j < actors.size(); j++){
                    for(stUint k = 0; k < 6; k++){
                        //TODO test this.
                        glBindFramebuffer(GL_FRAMEBUFFER, lights[i]->shadowFrameBuffer[k]);
                        glClear(GL_DEPTH_BUFFER_BIT);
                        glEnable(GL_CULL_FACE);
                        glCullFace(GL_FRONT);

                        actors[j]->setShdrUniform("lightSpaceMatrix", ortho * lights[j]->projections[k]);
                        actors[j]->draw(lights[i]->get<STGraphicsComponent>()->getMaterial());
                        glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    }
                }
            }
        }
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
    }

    if(getRenderMode() == RenderMode::FORWARD){
        glViewport(0, 0, WIDTH, HEIGHT);
        // Bind the frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        auto clearColor = STGraphics::ClearColor;
        glClearColor(0,0,0,1);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, velocityTexture, 0);

        glClear(GL_COLOR_BUFFER_BIT);

        //Depth Pre-Pass
        for(int i =0; i< actors.size(); i++){
            actors[i]->draw(m_velocityMat);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);


        glClearColor(clearColor.getX(), clearColor.getY(), clearColor.getZ(), clearColor.getZ());
        glClear(GL_COLOR_BUFFER_BIT);

        rendScene->drawSkybox(*getActiveCamera());

        glDisable(GL_BLEND);
        glDepthFunc(GL_EQUAL);
        glDepthMask(GL_TRUE);

        for(stUint i =0; i < actors.size(); i++){
            actors[i]->setShdrUniform("_CameraPos", getActiveCamera()->transform()->getTranslate());
            actors[i]->setShdrUniform_CubeMap("_WorldCubeMap", rendScene->m_skybox);
            actors[i]->setShdrUniform_Texture2DArray("shadowArray", shadowArray, 1);
            actors[i]->setShdrUniform("LightCount", (stInt)lights.size());
            for(stUint j =0; j < lights.size(); j++) {
                auto lightProps = lights[j]->get<STLightComponent>()->getProperties();
                auto shadowProps = lights[j]->get<STShadowComponent>()->getProperties();

                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].LightType", (stInt)lightProps->direction.getW());
                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Color", lightProps->color);
                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Position", lights[j]->transform()->getTranslate());
                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Direction", lightProps->direction);
                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Radius", lightProps->radius);
                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].Intensity", lightProps->intensity);
                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].UseShadow", lightProps->useShadow);
                actors[i]->setShdrUniform("Light["+std::to_string(j)+"].ShadowIndex", (stInt)shadowProps->shadowIndex);
            }
            actors[i]->draw();
        }


        glDisable(GL_BLEND);
        glDepthFunc(GL_LESS);
        glDepthMask(GL_TRUE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);

        glDisable(GL_CULL_FACE);
    }else if(getRenderMode() == RenderMode::DEFERRED){
        glViewport(0, 0, WIDTH, HEIGHT);

        glBindBuffer(GL_FRAMEBUFFER, frameBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, velocityTexture, 0);

        //Predepth pass for velocity
        for(auto actor : actors){
            actor->draw(m_velocityMat);
        }

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexBuffer, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        //Geometry Pass
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        for(stUint i = 0, S = actors.size(); i < S; i++){
            actors[i]->draw(m_GBufferOverrideMat, true);
        }
        glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        Deff_LightPassShdr->bind();
        Deff_LightPassShdr->update("gPosition", 0);
        Deff_LightPassShdr->update("gNormal", 1);
        Deff_LightPassShdr->update("gColorSpec", 2);
        Deff_LightPassShdr->update("gMRA", 3);
        Deff_LightPassShdr->update("gTangent", 4);
        Deff_LightPassShdr->update("shadowArray", 5);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, gColorSpec);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, gMRA);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, gTangent);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D_ARRAY, shadowArray);
        Deff_LightPassShdr->update("LightCount", (stInt)lights.size());
        Deff_LightPassShdr->update_CubeMap("_WorldCubeMap", rendScene->m_skybox);
        for(stUint i = 0, S = (stUint)lights.size(); i < S; i++){
            auto lightProps = lights[i]->get<STLightComponent>()->getProperties();
            auto shadowProps = lights[i]->get<STShadowComponent>()->getProperties();
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].LightType", (stInt)lightProps->direction.getW());
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].Color", lightProps->color);
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].Position", lights[i]->transform()->getTranslate());
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].Direction", lightProps->direction);
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].Radius", lightProps->radius);
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].Intensity", lightProps->intensity);
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].UseShadow", lightProps->useShadow);
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].ShadowIndex", (stInt)shadowProps->shadowIndex);
            Deff_LightPassShdr->update("Light["+std::to_string(i)+"].LightSpaceMatrix", shadowProps->projections[0]);
        }
        Deff_LightPassShdr->update("viewPos", getActiveCamera()->transform()->getTranslate());
        screenQuad->draw();

        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
        glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glDepthFunc(GL_LEQUAL);

        rendScene->drawSkybox(*getActiveCamera());
        glDisable(GL_BLEND);
        glDepthFunc(GL_LESS);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
    }

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

void GLGraphics::initScene(STScene *scene) {
    scene->setRenderScene(new GLRenderScene());
}

void GLGraphics::cleanup() {
    std::cout << "Clearing Graphics" << std::endl;
    for(auto c : characters){
        glDeleteTextures(1, &c.second.texID);
    }
    glDeleteBuffers(1, &textVBO);
    glDeleteBuffers(1, &velocityBuffer);

    glDeleteVertexArrays(1, &textVAO);
    glDeleteFramebuffers(1, &frameBuffer);
    glDeleteFramebuffers(1, &gBuffer);
    glDeleteFramebuffers(1, &bloomThresBuf);
    glDeleteRenderbuffers(1, &rendBuffer);
    glDeleteRenderbuffers(1, &rboDepth);
    glDeleteTextures(1, &frameTexBuffer);
    glDeleteTextures(1, &gPosition);
    glDeleteTextures(1, &gNormal);
    glDeleteTextures(1, &gMRA);
    glDeleteTextures(1, &gColorSpec);
    glDeleteTextures(1, &gTangent);
    glDeleteTextures(1, &shadowArray);
    glDeleteTextures(1, &velocityTexture);
    glDeleteTextures(1, &bloomThresTex);

    delete m_directionalLightMat;
    delete m_pointLightMat;
    delete m_albedoMat;
    delete m_IBLMat;
    delete m_velocityMat;
    delete Deff_LightPassShdr;
    delete screenQuad;

    delete textShader;
    delete screenShdr;
    delete Bloom_Composite;
    delete Bloom_Threshold;
    delete Motion_Blur;
    delete Tone_Mapping;

}

void GLGraphics::loadFont(const std::string &) {
    //TODO Imlement this.
}

void GLGraphics::setResolution(stUint w, stUint h) {
    WIDTH = w;
    HEIGHT = h;
    cleanup();
    glViewport(0, 0, w, h);
    init(w, h);
}

/**
 * Uses a custom screen shader to render the sceen.
 * @param shdrPath
 */
void GLGraphics::setScreenShader(const std::string &shdrPath) {
    screenShdr = new GLShader("screen", shdrPath);
}

