#ifndef WAHOO_GLGRAPHICS_H
#define WAHOO_GLGRAPHICS_H

#include "../../../ext/GL/glew.h"
#include "../../STLight.h"
#include "../../STEntity.h"
#include "../../STSceneManager.h"
#include "../STGraphics.h"
#include "GLShader.h"
#include "GLTexture.h"


class GLGraphics;

struct STRenderPass;

struct GLRenderPass : public STRenderPass{
    unsigned int width, height;
    GLShader* shdr;
    GLTexture* tex;
    STMeshComponent* mesh;
    GLuint frameBuffer;
    GLuint texBuffer;
    GLuint renderBuffer;
    std::vector<STEntity*> entities;
    std::vector<STLight*> lights;

    GLRenderPass();
    GLRenderPass(unsigned int x, unsigned int y);
    GLRenderPass(unsigned int x, unsigned int y, std::string& name);
    ~GLRenderPass();

    void bind();
    void unbind();

    void setEntities(std::vector<STEntity*> _entities);
    void setLights(std::vector<STLight*> _lights);

    void draw(GLGraphics* g);
};

class GLGraphics : public STGraphics{
public:
    GLGraphics();
    GLGraphics(STGame*);

    virtual void addRenderPass(STSceneManager* scene){

    }

    virtual void drawScene(STSceneManager* scene);
protected:

private:
    std::vector<STRenderPass*> renderPass;
};


#endif //WAHOO_GLGRAPHICS_H
