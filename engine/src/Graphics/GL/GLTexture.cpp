#include "GLTexture.h"

GLTexture::GLTexture() {
    m_texIndex = 0;
    m_texCount = 0;
}

GLTexture::GLTexture(const std::string &fileName) {
    m_texIndex = 0;
    m_fileReference.push_back(fileName);
    reBind();
    m_texCount = 1;
}

void GLTexture::addTexture(const std::string &fileName) {
    m_fileReference.push_back(fileName);
    reBind();
    m_texCount++;
}

void GLTexture::addTexture(const std::string &fileName, int ind) {
    m_texCount++;
    SDL_Surface* img = NULL;
    img = IMG_Load(fileName.c_str());
    if(img == NULL){
        std::cout << "Error: " << IMG_GetError() << std::endl;
    }
    glGenTextures(1, m_tex);
    glActiveTexture(GL_TEXTURE0 + ind);
    glBindTexture(GL_TEXTURE_2D, m_tex[0]);
    GLenum mode = getMode(img->format->BytesPerPixel, img->format->Rmask);

    m_texWidth = (uint32_t)img->w;
    m_texHeight = (uint32_t)img->h;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, mode, img->w, img->h, 0, mode, GL_UNSIGNED_BYTE, img->pixels);
    SDL_FreeSurface(img);
    img = 0;
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

    m_texWidth = (uint32_t)img->w;
    m_texHeight = (uint32_t)img->h;

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

GLenum  GLTexture::getMode(int numOfColors, int mask) {
    if(numOfColors == 4){
        if(mask == 0x000000ff) return GL_RGBA;
        else return GL_BGRA;
    }else if(numOfColors == 3){
        if(mask == 0x000000ff) return GL_RGB;
        else return GL_BGR;
    }else{
        return GL_FALSE;
    }
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

        m_texWidth = (uint32_t)img->w;
        m_texHeight = (uint32_t)img->h;

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

    //glEnable(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, m_tex[0]);
}

GLuint GLTexture::loadCubemapTexture(const std::string &fileName) {
    std::vector<std::string> faces;
    faces.push_back(fileName+"/right.jpg");
    faces.push_back(fileName+"/left.jpg");
    faces.push_back(fileName+"/top.jpg");
    faces.push_back(fileName+"/bottom.jpg");
    faces.push_back(fileName+"/back.jpg");
    faces.push_back(fileName+"/front.jpg");
    GLuint texID;
    glGenTextures(1, &texID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    SDL_Surface* img = NULL;
    for(uint32_t i = 0, S = faces.size(); i < S; i++){
        img = IMG_Load(faces[i].c_str());
        if(img == NULL){
            std::cout << "Could not find " << faces[i].c_str() << std::endl;
            break;
        }
        GLenum  mode = getMode(img->format->BytesPerPixel, img->format->Rmask);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, mode, img->w, img->h, 0, mode, GL_UNSIGNED_BYTE, img->pixels);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return texID;
}


unsigned int GLTexture::getTextureCount() {
    return m_texCount;
}
