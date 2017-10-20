#ifndef WAHOO_TEXTURE_H
#define WAHOO_TEXTURE_H

#include <string>

class Texture {
public:
    Texture(){ }
    Texture(const std::string& fileName){}

    virtual ~Texture(){}
    virtual void addTexture(const std::string& fileName){ }
    virtual void addTexture(const std::string& fileName, int ind){ }
    virtual void bind(unsigned int index){ }
    virtual unsigned int getTextureCount(){ return 32; }
    virtual unsigned int getTextureWidth(){ return 0; }
    virtual unsigned int getTextureHeight(){ return 0; }
protected:
    virtual void reBind(){ }
    uint32_t m_texWidth, m_texHeight, m_texCount;
private:

};


#endif //WAHOO_TEXTURE_H
