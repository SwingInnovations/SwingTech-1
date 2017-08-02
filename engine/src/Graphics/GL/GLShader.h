#ifndef WAHOO_GLSHADER_H
#define WAHOO_GLSHADER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

#if __MINGW32__
#include "../../../include/GL/glew.h"
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../Shader.h"
#include "../Camera.h"
#include "../../Math/Vector.h"

class GLShader : public Shader{
public:
    GLShader();

    explicit GLShader(const std::string& filePath);
    GLShader(const std::string& vShaderPath, const std::string& fShaderPath);

    void bind() override ;
    void unbind() override;
    void update(Transform& trans) override;
    void update(Camera& cam) override;
    void update(Transform& trans, Camera& cam) override;
    void update(const std::string& name, int val) override;
    void update(const std::string& name, float val) override;
    void update(const std::string& name, Vector2<stReal> val) override;
    void update(const std::string& name, Vector3<stReal> val) override;
    void update(const std::string& name, Vector4<stReal> val) override;
    void update(const std::string& name, Matrix4f /*mat*/);
    void update(const std::string& name, Matrix4f&, bool);
    void update_Texture(const std::string& name, stUint id) override;
    void update_Texture(const std::string& name, Vector2<stInt> val) override;
    void update_Texture2DArray(const std::string& name, Vector2<stInt> val) override;
    void update_CubeMap(const std::string& name, stUint id) override;

    std::string getShaderName() override { return m_shaderName; }

    virtual ~GLShader();
private:
    static const unsigned int NUM_SHADER = 2;
    enum ShaderType{VERTEX_SHADER, FRAGMENT_SHADER};

    void checkShaderStatus(GLuint, GLuint, bool, const std::string&);
    std::string loadShader(const std::string& filePath);
    GLuint createShader(const std::string& text, unsigned int type);

    std::string m_shaderName;
    std::string m_fragShaderName;

    GLuint m_Program;
    GLuint m_Shaders[NUM_SHADER];
    GLuint m_uniforms[6]; // 3 pre-defined uniforms that are essential
    Matrix4f m_cachedMVP;

};


#endif //WAHOO_GLSHADER_H
