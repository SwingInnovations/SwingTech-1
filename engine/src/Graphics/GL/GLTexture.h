#ifndef WAHOO_GLTEXTURE_H
#define WAHOO_GLTEXTURE_H

#include <vector>
#include <string>
#include <iostream>
#include <cassert>

#if __MINGW32__
#include "../../../include/GL/glew.h"
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../../include/SDL2/SDL_image.h"
#include "../Texture.h"

class GLTexture : public Texture{
public:
    GLTexture();

    explicit GLTexture(const std::string& fileName);
    virtual ~GLTexture();

    GLuint genTex(const std::string& fileName);

    /**
     *  Generates a GL Texture Handle
     * @param fileName
     * @return
     */
    static GLuint GenTex(const std::string& fileName);
    /**
     * Disposes a given Texture Handle
     * @param texHandle
     */
    static void   DisposeTex(GLuint texHandle);

	[[deprecated]]
    void addTexture(const std::string& fileName) override;
	[[deprecarted]]
    void addTexture(const std::string& fileName, int ind) override;
    void bind(unsigned int index) override;
    unsigned int getTextureCount() override;
    static GLenum getMode(int, int);

    /**
     * Gets Texture width.
     * @return
     */
    unsigned int getTextureWidth() override { return m_texWidth; }
    /**
     * Get Texture Height;
     * @return
     */
    unsigned int getTextureHeight() override { return m_texHeight; }

    /** Loads a cubemap.
     *
     * @param fileName
     * @return Uint id of the texture loaded in OpenGL.
     */
    static GLuint loadCubemapTexture(const std::string& fileName);

protected:
    void reBind() override;
private:
    GLuint m_tex[32];
    unsigned int m_texIndex;
    std::vector<std::string> m_fileReference;
};


#endif //WAHOO_GLTEXTURE_H
