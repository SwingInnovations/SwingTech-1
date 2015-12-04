#include "GLShader.h"

GLShader::GLShader() {
    m_Program = glCreateProgram();
    m_Shaders[0] = createShader(loadShader("standardShader.vsh"), GL_VERTEX_SHADER);
    m_Shaders[1] = createShader(loadShader("standardShader.fsh"), GL_FRAGMENT_SHADER);
    for(unsigned int i = 0; i < NUM_SHADER; i++){
        glAttachShader(m_Program, m_Shaders[i]);
    }

    glBindAttribLocation(m_Program, 0, "position");
    glBindAttribLocation(m_Program, 1, "texCoord");
    glBindAttribLocation(m_Program, 2, "normal");
    glBindAttribLocation(m_Program, 3, "tangent");
    glBindAttribLocation(m_Program, 4, "biTangent");

    glLinkProgram(m_Program);
    checkShaderStatus(m_Program, GL_LINK_STATUS, true, "Error Linking Shader Program");

    glValidateProgram(m_Program);
    checkShaderStatus(m_Program, GL_LINK_STATUS, true, "Invalid Shader Program");

    m_uniforms[0] = glGetUniformLocation(m_Program, "model");
    m_uniforms[1] = glGetUniformLocation(m_Program, "camera");
    m_uniforms[2] = glGetUniformLocation(m_Program, "cameraPosition");
}

GLShader::GLShader(const std::string &filePath) {
    m_Program = glCreateProgram();
    m_Shaders[0] = createShader(loadShader(filePath + ".vsh"), GL_VERTEX_SHADER);
    m_Shaders[1] = createShader(loadShader(filePath + ".fsh"), GL_FRAGMENT_SHADER);
    for(unsigned int i = 0; i < NUM_SHADER; i++){
        glAttachShader(m_Program, m_Shaders[i]);
    }

    glBindAttribLocation(m_Program, 0, "position");
    glBindAttribLocation(m_Program, 1, "texCoord");
    glBindAttribLocation(m_Program, 2, "normal");
    glBindAttribLocation(m_Program, 3, "tangent");
    glBindAttribLocation(m_Program, 4, "biTangent");

    glLinkProgram(m_Program);
    checkShaderStatus(m_Program, GL_LINK_STATUS, true, "Error Linking Shader Program");

    glValidateProgram(m_Program);
    checkShaderStatus(m_Program, GL_LINK_STATUS, true, "Invalid Shader Program");

    m_uniforms[0] = glGetUniformLocation(m_Program, "model");
    m_uniforms[1] = glGetUniformLocation(m_Program, "camera");
    m_uniforms[2] = glGetUniformLocation(m_Program, "cameraPosition");
}

GLShader::GLShader(const std::string &vShaderPath, const std::string &fShaderPath) {
    m_Program = glCreateProgram();
    m_Shaders[0] = createShader(loadShader(vShaderPath + ".vsh"), GL_VERTEX_SHADER);
    m_Shaders[1] = createShader(loadShader(fShaderPath + ".fsh"), GL_FRAGMENT_SHADER);
    for(unsigned int i = 0; i < NUM_SHADER; i++){
        glAttachShader(m_Program, m_Shaders[i]);
    }

    glBindAttribLocation(m_Program, 0, "position");
    glBindAttribLocation(m_Program, 1, "texCoord");
    glBindAttribLocation(m_Program, 2, "normal");
    glBindAttribLocation(m_Program, 3, "tangent");
    glBindAttribLocation(m_Program, 4, "biTangent");

    glLinkProgram(m_Program);
    checkShaderStatus(m_Program, GL_LINK_STATUS, true, "Error Linking Shader Program");

    glValidateProgram(m_Program);
    checkShaderStatus(m_Program, GL_LINK_STATUS, true, "Invalid Shader Program");

    m_uniforms[0] = glGetUniformLocation(m_Program, "model");
    m_uniforms[1] = glGetUniformLocation(m_Program, "camera");
    m_uniforms[2] = glGetUniformLocation(m_Program, "cameraPosition");
}

GLShader::~GLShader() {
    for(unsigned int i = 0; i < NUM_SHADER; i++){
        glDetachShader(m_Program, m_Shaders[i]);
    }
    glDeleteProgram(m_Program);
}

void GLShader::bind() {
    glUseProgram(m_Program);
}

void GLShader::update(Transform& trans){
    Matrix4f transform;
    transform = trans.getModel();
        glUniformMatrix4fv(m_uniforms[0], 1, GL_TRUE,  &transform.m[0][0]);
}

void GLShader::update(Camera& cam){
    Matrix4f camera;
    camera = cam.getViewProjection();
    glUniformMatrix4fv(m_uniforms[1], 1, GL_TRUE, &camera.m[0][0]);
}

void GLShader::update(Transform& trans, Camera& cam){
    Matrix4f transform, camera;
    transform = trans.getModel();
    camera = cam.getViewProjection();
    Vector3<stReal> camPos = cam.transform()->getTranslate<stReal>();

    glUniformMatrix4fv(m_uniforms[0], 1, GL_TRUE, &transform.m[0][0]);
    glUniformMatrix4fv(m_uniforms[1], 1, GL_TRUE, &camera.m[0][0]);
    glUniform3f(m_uniforms[2], camPos.getX(), camPos.getY(), camPos.getZ());
}

void GLShader::update(const std::string &name, int val) {
    glUniform1i(glGetUniformLocation(m_Program, name.c_str()), val);
}

void GLShader::update(const std::string& name, float val) {
    glUniform1f(glGetUniformLocation(m_Program, name.c_str()), val);
}

void GLShader::update(const std::string &name, Vector3<stReal> val) {
    glUniform3f(glGetUniformLocation(m_Program, name.c_str()), val.getX(), val.getY(), val.getZ());
}

void GLShader::update(const std::string &name, Vector4<stReal> val) {
    glUniform4f(glGetUniformLocation(m_Program, name.c_str()), val.getX(), val.getY(), val.getZ(), val.getW());
}

void GLShader::checkShaderStatus(GLuint shaderID, GLuint flag, bool isProgram, const std::string &errMsg) {
    GLint success = 0;
    GLchar error[1024] = {0};

    if(isProgram){
        glGetProgramiv(shaderID, flag, &success);
    }else{
        glGetShaderiv(shaderID, flag, &success);
    }

    if(success == GL_FALSE){
        if(isProgram){
            glGetProgramInfoLog(shaderID, sizeof(error), NULL, error);
        }else{
            glGetShaderInfoLog(shaderID, sizeof(error), NULL, error);
        }
    }

    std::cerr << errMsg << " : " << error << std::endl;
}

std::string GLShader::loadShader(const std::string &filePath) {
    std::ifstream file;
    file.open(filePath.c_str());

    if(!file.good()){

    }

    std::string output;
    std::string line;

    if(file.is_open()){
        while(file.good()){
            std::getline(file, line);
            output.append(line + "\n");

        }
    }
    return output;
}

GLuint GLShader::createShader(const std::string &text, unsigned int type) {
    GLuint shader = glCreateShader(type);
    if(shader == 0){
        //TODO - Make err msg
    }

    const GLchar*p [1];
    p[0] = text.c_str();
    GLint length[1];
    length[0] = text.length();

    glShaderSource(shader, 1, p, length);
    glCompileShader(shader);
    return shader;
}