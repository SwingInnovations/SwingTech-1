#include "Shader.h"

/**
 * Legacy Function -> To Be Deprecated
 * @param _uniforms
 */
void Shader::updateUniforms(std::vector<STShader::ShaderAttrib> _uniforms) {
    for(uint32_t i = 0, S = (uint32_t)_uniforms.size(); i < S; i++){
        if(_uniforms[i].type == STShader::INT){
            update(_uniforms[i].name, STShader::toInt(_uniforms[i].value));
        }else if(_uniforms[i].type == STShader::FLOAT){
            update(_uniforms[i].name, STShader::toFloat(_uniforms[i].value));
        } else if(_uniforms[i].type == STShader::VEC3){
            update(_uniforms[i].name, STShader::toVector3(_uniforms[i].value));
        }else if(_uniforms[i].type == STShader::VEC4){
            update(_uniforms[i].name, STShader::toVector4(_uniforms[i].value));
        }else if(_uniforms[i].type == STShader::MAT4){
            update(_uniforms[i].name, STShader::toMatrix4f(_uniforms[i].value));
        }else if(_uniforms[i].type == STShader::TEX){
            auto vec = STShader::toVector2(_uniforms[i].value);
            update_Texture(_uniforms[i].name, Vector2<stInt>((stInt)vec.getX(), (stInt)vec.getY()));
        }else if(_uniforms[i].type == STShader::CUBE_MAP){
            update_CubeMap(_uniforms[i].name, STShader::toSTUint(_uniforms[i].value));
        }else if(_uniforms[i].type == STShader::TEX2DARR){
            auto vec = STShader::toVector2(_uniforms[i].value);
            update_Texture2DArray(_uniforms[i].name, Vector2<stInt>((stInt)vec.getX(), (stInt)vec.getY()));
        }
    }
}

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
