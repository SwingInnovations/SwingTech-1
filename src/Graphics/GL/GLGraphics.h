#ifndef WAHOO_GLGRAPHICS_H
#define WAHOO_GLGRAPHICS_H

#include <regex>

#include "../../../ext/GL/glew.h"
#include "../../STLight.h"
#include "../../STEntity.h"
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
    std::vector<STLight*> lights;

    GLRenderPass();
    GLRenderPass(unsigned int x, unsigned int y);
    GLRenderPass(unsigned int x, unsigned int y, std::string& name);
    GLRenderPass(unsigned int x, unsigned int y, GLShader* shdr);
    ~GLRenderPass();

    void bind();
    void unbind();

    void drawSkybox(GLGraphics* g);

    void setScene(STSceneManager*);

    void setEntities(std::vector<STEntity*> _entities);
    void setLights(std::vector<STLight*> _lights);

    void draw(GLGraphics* g);
};

class GLGraphics : public STGraphics{
public:
    GLGraphics();
    GLGraphics(STGame*);

    virtual void addRenderPass(STSceneManager* scene){
        renderPass.push_back(new GLRenderPass(WIDTH, HEIGHT));
        renderPass.back()->setEntities(scene->getEntities());
    }

    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize );
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal value);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector2<stReal> vector);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2, stReal v3);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector3<stReal> vector);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, stReal v1, stReal v2, stReal v3, stReal v4);
    void drawText(Vector2<stReal> pos, const std::string& text, stReal fontSize, Vector4<stReal> vector);

    void addRenderPass(STSceneManager* scene, GLShader* shdr);

    virtual void setShader(int,Shader*);

    virtual void drawScene(STSceneManager* scene);
    static Vector3<stReal> TextColor;
protected:

private:
    std::vector<GLRenderPass*> renderPass;
    std::map<GLchar, Character> characters;
    GLuint textVAO;
    GLuint textVBO;
    GLShader* textShader;
    Matrix4f orthoProjection;
};


#endif //WAHOO_GLGRAPHICS_H
