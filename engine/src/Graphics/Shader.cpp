#include "Shader.h"

void Shader::updateUniforms(std::map<std::string, STShader::ShaderAttrib> m_uniforms) {
    for(auto uniform : m_uniforms){
        auto value = uniform.second.value;
        if(uniform.second.type == STShader::INT) update(uniform.second.name, STShader::toInt(value));
        else if(uniform.second.type == STShader::FLOAT) update(uniform.second.name, STShader::toFloat(value));
        else if(uniform.second.type == STShader::VEC2) update(uniform.second.name, STShader::toVector2(value));
        else if(uniform.second.type == STShader::VEC3) update(uniform.second.name, STShader::toVector3(value));
        else if(uniform.second.type == STShader::VEC4) update(uniform.second.name, STShader::toVector4(value));
        else if(uniform.second.type == STShader::MAT4) update(uniform.second.name, STShader::toMatrix4f(value));
        else if(uniform.second.type == STShader::TEX){
            auto vec = STShader::toVector2(value);
            update_Texture(uniform.second.name, Vector2<stInt>((stInt)vec.getX(), (stInt)vec.getY()));
        }else if(uniform.second.type == STShader::CUBE_MAP) update_CubeMap(uniform.second.name, STShader::toSTUint(value));
        else if(uniform.second.type == STShader::TEX2DARR){
            auto vec = STShader::toVector2(value);
            update_Texture2DArray(uniform.second.name, Vector2<stInt>((stInt)vec.getX(), (stInt)vec.getY()));
        }
    }
}