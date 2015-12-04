#ifndef WAHOO_GLSHADER_H
#define WAHOO_GLSHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "../../../ext/GL/glew.h"
#include "../Shader.h"
#include "../Camera.h"
#include "../../Math/Vector.h"

class GLShader : public Shader{
public:
    GLShader();
    GLShader(const std::string& filePath);
    GLShader(const std::string& vShaderPath, const std::string& fShaderPath);

    void bind();
    void update(Transform& trans);
    void update(Camera& cam);
    void update(Transform& trans, Camera& cam);
    void update(const std::string& name, int val);
    void update(const std::string& name, float val);
    void update(const std::string& name, Vector3<stReal> val);
    void update(const std::string& name, Vector4<stReal> val);

    virtual ~GLShader();
private:
    static const unsigned int NUM_SHADER = 2;
    enum ShaderType{VERTEX_SHADER, FRAGMENT_SHADER};

    void checkShaderStatus(GLuint, GLuint, bool, const std::string&);
    std::string loadShader(const std::string& filePath);
    GLuint createShader(const std::string& text, unsigned int type);

    //Buffer Data
    GLuint m_Program;
    GLuint m_Shaders[NUM_SHADER];
    GLuint m_uniforms[3]; // 3 pre-defined uniforms that are essential

};


#endif //WAHOO_GLSHADER_H
