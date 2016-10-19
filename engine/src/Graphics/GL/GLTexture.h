#ifndef WAHOO_GLTEXTURE_H
#define WAHOO_GLTEXTURE_H

#include <vector>
#include <string>
#include <iostream>
#include <cassert>

#include "../../../include/GL/glew.h"
#include "../../../include/SDL2/SDL_image.h"
#include "../Texture.h"

class GLTexture : public Texture{
public:
    GLTexture();
    GLTexture(const std::string& fileName);
    virtual ~GLTexture();

    GLuint genTex(const std::string& fileName);
    static GLuint GenTex(const std::string& fileName);
    void addTexture(const std::string& fileName);
    void addTexture(const std::string& fileName, int ind);
    void bind(unsigned int index);
    unsigned int getTextureCount();
    static GLenum getMode(int, int);

    unsigned int getTextureWidth(){ return m_texWidth; }
    unsigned int getTextureHeight(){ return m_texHeight; }

    static GLuint loadCubemapTexture(const std::string& fileName);

protected:
    void reBind();
private:
    GLuint m_tex[32];
    unsigned int m_texIndex;
    std::vector<std::string> m_fileReference;
};


#endif //WAHOO_GLTEXTURE_H
