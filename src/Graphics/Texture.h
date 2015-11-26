#ifndef WAHOO_TEXTURE_H
#define WAHOO_TEXTURE_H

#include <string>

class Texture {
public:
    Texture(){ }
    Texture(const std::string& fileName){}
    ~Texture(){}
    virtual void addTexture(const std::string& fileName){ }
    virtual void bind(unsigned int index){ }
    virtual unsigned int getTextureCount(){ return -1; }
protected:
    virtual void reBind(){ }
private:

};


#endif //WAHOO_TEXTURE_H
