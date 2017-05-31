#ifndef WAHOO_STMATERIAL_H
#define WAHOO_STMATERIAL_H

#include <map>
#include <string>

#include "Texture.h"
#include "Shader.h"
#include "GL/GLTexture.h"
#include "STColor.h"

class GLTexture;
class STGraphics;

struct ShaderList{
    std::string vertShader;
    std::string fragShader;
    std::string geomShader;
};

struct TextureList{
    std::string diffuseTex;
    std::string normalTex;
    std::string specularTex;
    std::string alphaTex;
};

class STMaterial{
public:
    STMaterial();

    STMaterial(ShaderList, TextureList);

    /*!
     * @name STMaterial
     * @param shdr STShader for use
     * @return
     */
    STMaterial(Shader* shdr);

    STMaterial(Shader* shdr, Texture* tex){
        shader = shdr;
        initBaseUniforms();

    }

    STMaterial* copy();

    ~STMaterial(){
        delete shader;

    }

    void setUniforms(std::map<std::string, STShader::ShaderAttrib> newUniforms);

    static STMaterial* CreateStandardMaterial(){
        return new STMaterial({"standard", "standard"}, {});
    }

    static STMaterial* CreateStandardPBRMaterial(){
        return new STMaterial({"standard", "standardPBR"}, {});
    }

    /*!
     * @param fileName Adds diffuse texture and assigns to texture index 0
     */
    void setDiffuseTexture(const std::string& fileName);
    void setDiffuseColor(STColor);
    void setNormalTexture(const std::string& fileName);
    void setMetallic(stReal);
    void setMetallic(const std::string& fileName);
    void setRoughness(stReal);
    void setRoughness(const std::string& fileName);

    void setBaseColor(Vector3<stReal> color){
        m_baseColor = color;
    }

    std::map<std::string, STShader::ShaderAttrib>& GetUniforms(){ return m_Uniforms; };

    void initBaseUniforms()
     {
         setBaseColor( Vector3<stReal>(1,1,1) );

        //Initialize for map
         m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Diffuse_Color", STShader::ShaderAttrib("Material.Diffuse_Color", STShader::VEC4, STShader::toString(Vector4<stReal>(1.f, 0.f, 0.f, 1.f)))));
         m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Normal_Use", STShader::ShaderAttrib("Material.Normal_Use", STShader::INT, STShader::toString(0))));
         m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Metallic_Value", STShader::ShaderAttrib("Material.Metallic_Value", STShader::VEC2, STShader::toString(Vector2<stReal>(0.f, 1.f)))));
         m_Uniforms.insert(std::pair<std::string, STShader::ShaderAttrib>("Material.Roughness_Value", STShader::ShaderAttrib("Material.Roughness_Value", STShader::VEC2, STShader::toString(Vector2<stReal>(0.f, 1.f)))));
     }


    /*!
     * @details Main update that gets called in the render loop.
     */
    inline void update(){
        shader->bind();
        shader->updateUniforms(m_Uniforms);
    }

    Shader* shdr(){ return shader; }

    inline void update(std::vector<STShader::ShaderAttrib> entityUniforms){
        shader->bind();
        shader->updateUniforms(m_Uniforms);
        shader->updateUniforms(entityUniforms);
    }

    void draw(std::map<std::string, STShader::ShaderAttrib>& entityUniforms, Transform& T, Camera& C);
    void draw(std::map<std::string, STShader::ShaderAttrib>& entityUniform, std::map<std::string, STShader::ShaderAttrib> originalMaterialUniforms, Transform &T, Camera& C);
private:
    void init_GLShaders(ShaderList list);
    void init_GLTextures(TextureList list);
    Shader* shader;
    Vector3<stReal> m_baseColor;
    std::map<std::string, STShader::ShaderAttrib> m_Uniforms;
};

#endif //WAHOO_STMATERIAL_H
