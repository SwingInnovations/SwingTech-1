#ifndef WAHOO_GLGRAPHICS_H
#define WAHOO_GLGRAPHICS_H

#include <regex>

#include "../../../include/GL/glew.h"
#include "../../Entity/STLight.h"
#include "../../Entity/STEntity.h"
#include "../../STSceneManager.h"
#include "../STGraphics.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLMesh.h"


class GLGraphics;

struct STRenderPass;

struct Character{
    GLuint texID;
    Vector2<int> size;
    Vector2<int> bearing;
    GLuint Advance;
};

struct GLRenderPass : public STRenderPass{
    unsigned int width, height;
    GLShader* postShader;
    GLTexture* tex;
    STMeshComponent* mesh;
    GLMesh* skyboxMesh;
    GLuint frameBuffer;
    GLuint texBuffer;
    GLuint renderBuffer;
    GLuint skyBox;
    GLShader* skyboxShdr;
    std::vector<STEntity*> entities;
    std::vector<STActor*> actors;
    std::vector<STLight*> lights;

    GLRenderPass();
    GLRenderPass(unsigned int x, unsigned int y);
    GLRenderPass(unsigned int x, unsigned int y, std::string& name);
    GLRenderPass(unsigned int x, unsigned int y, GLShader* shdr);
    ~GLRenderPass();

    void bind();
    void unBind();

    void drawSkybox(GLGraphics* g);

    void setScene(STSceneManager*);
    void setScene(STScene*);

    void setEntities(std::vector<STEntity*> _entities);
    void setLights(std::vector<STLight*> _lights);

    void draw(GLGraphics* g);
};

struct RenderScene{
    RenderScene(){
        m_skybox = 0;
        m_skyboxShdr = nullptr;
        m_initiated = false;
        skyboxMesh = new GLMesh(new STCube(1000));
    }

    inline void initSkybox(const std::string& shdr, const std::string& map){
        m_skybox = GLTexture::loadCubemapTexture(map);
        m_skyboxShdr = new GLShader(shdr);
    }

    inline void drawSkybox(Camera& cam){
        glDisable(GL_CULL_FACE);
        glDepthFunc(GL_LEQUAL);
        m_skyboxShdr->bind();
        m_skyboxShdr->update(cam);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox);
        skyboxMesh->draw();
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }

    GLuint m_skybox;
    GLShader* m_skyboxShdr;
    GLMesh* skyboxMesh;
    bool m_initiated;
};

class GLGraphics : public STGraphics{
public:
    GLGraphics();
    GLGraphics(STGame*);

    virtual void addRenderPass(STSceneManager* scene){
        renderPass.push_back(new GLRenderPass(WIDTH, HEIGHT));
        renderPass.back()->setEntities(scene->getEntities());
    }

    inline void addRenderPass(STScene* scene, GLShader* shdr){
        renderPass.push_back(new GLRenderPass(WIDTH, HEIGHT, shdr));
        renderPass.back()->setScene(scene);
    }

    std::string getVendor();

    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize );
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal>* color);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, std::string& msg);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector2<stReal> vector);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2, stReal v3);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector3<stReal> vector);
    void addRenderPass(STSceneManager* scene, GLShader* shdr);

    virtual void setShader(int,Shader*);

    virtual void drawScene(STSceneManager* scene);
    virtual void drawScene(STScene* scene);
    virtual void initScene(stUint index);
    static Vector3<stReal> TextColor;
protected:

private:
    std::vector<GLRenderPass*> renderPass;
    std::map<GLchar, Character> characters;
    std::map<stUint, RenderScene> scenes;
    GLuint textVAO;
    GLuint textVBO;
    GLShader* textShader;
    Matrix4f orthoProjection;
    GLuint frameBuffer;
    GLuint frameTexBuffer;
    GLuint rendBuffer;
    GLShader* screenShdr;
    GLMesh* screenQuad;
};


#endif //WAHOO_GLGRAPHICS_H
