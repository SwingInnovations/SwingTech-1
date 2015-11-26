#include "GLTexture.h"

GLTexture::GLTexture() {
    m_texIndex = 0;
}

GLTexture::GLTexture(const std::string &fileName) {
    m_texIndex = 0;
    m_fileReference.push_back(fileName);
    reBind();
}

void GLTexture::addTexture(const std::string &fileName) {
    m_fileReference.push_back(fileName);
    reBind();
}

GLTexture::~GLTexture() {
    glDeleteTextures(1, m_tex);

    m_fileReference.clear();
}

GLuint GLTexture::genTex(const std::string& filename){
    SDL_Surface* img = NULL;
    img = IMG_Load(filename.c_str());
    if(img == NULL){
        std::cout << "Error: " << IMG_GetError() << std::endl;
    }
    m_texIndex = 0;
    glGenTextures(1, m_tex);
    glActiveTexture(GL_TEXTURE0 + m_texIndex);
    glBindTexture(GL_TEXTURE_2D, m_tex[0]);

    GLenum mode;
    GLint nOfColors = img->format->BytesPerPixel;
    if(nOfColors == 4){
        if(img->format->Rmask == 0x000000ff){
            mode = GL_RGBA;
        }else{
            mode = GL_BGRA;
        }
    }else if(nOfColors == 3){
        if(img->format->Rmask == 0x000000ff){
            mode = GL_RGB;
        }else{
            mode = GL_BGR;
        }
    }else{
        std::cout << "Invalid Texture!" << std::endl;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, mode, img->w, img->h, 0, mode, GL_UNSIGNED_BYTE, img->pixels);
    SDL_FreeSurface(img);
    img = 0;

    return m_tex[m_texIndex];
}

void GLTexture::reBind() {
    glGenTextures(1, m_tex);
    for(unsigned int i = 0; i < m_fileReference.size(); i++){
        SDL_Surface* img = NULL;
        img = IMG_Load(m_fileReference[i].c_str());
        if(img == NULL){std::cout << "Error: Failed to load image: " << IMG_GetError() << std::endl;}
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_tex[i]);
        GLenum mode;
        GLint nOfColors = img->format->BytesPerPixel;
        if(nOfColors == 4){
            if(img->format->Rmask == 0x000000ff){
                mode = GL_RGBA;
            }else{
                mode = GL_BGRA;
            }
        }else if(nOfColors == 3){
            if(img->format->Rmask == 0x000000ff){
                mode = GL_RGB;
            }else{
                mode = GL_BGR;
            }
        }else{
            std::cout << "Invalid Textures" << std::endl;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, mode, img->w, img->h, 0, mode, GL_UNSIGNED_BYTE, img->pixels);
        SDL_FreeSurface(img);
        img = 0;
    }
}

void GLTexture::bind(unsigned int index){
    assert(index >= 0 && index <= 31);

    glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_tex[index]);
}
