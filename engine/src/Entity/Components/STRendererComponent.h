#ifndef WAHOO_STGRAPHICSCOMPONENT_H
#define WAHOO_STGRAPHICSCOMPONENT_H

#include "../../Graphics/Shader.h"
#include "../../Graphics/Texture.h"
#include "STComponent.h"

#include "../../Math/Vector.h"
#include "../../Graphics/STMaterial.h"


class STComponent;

class STRendererComponent : public STComponent{
public:
    explicit STRendererComponent(std::shared_ptr<STMaterial> material);
    STRendererComponent(const STRendererComponent& copy);
    void initScriptingFunctions(sol::state& state) override;

    STRendererComponent();
    [[deprecated]]
    STRendererComponent(Shader* shdr);
    ~STRendererComponent() override {
        m_Material.reset();
        for(auto uniform : m_Uniforms){
            if(uniform.second.type == STShader::TEX) {
                auto texHandle = (stUint)STShader::toVector2(uniform.second.value).getX();
                glDeleteTextures(1, &texHandle);
            }
        }
    }

    void addShdrUniform(const std::string& name, int value);
    void addShdrUniform(const std::string& name, float value);
    void addShdrUniform(const std::string& name, Vector2<stReal> value);
    void addShdrUniform(const std::string& name, Vector3<stReal> value);
    void addShdrUniform(const std::string& name, Vector4<stReal> value);
    void addShdrUniform(const std::string& name, Matrix4f value);
    void addShdrUniform_Texture(const std::string& name, stUint value);
    void addShdrUniform_Texture2DArray(const std::string& name, stUint value);
    void addShdrUniform_CubeMap(const std::string& name, stUint value);
    void setDiffuseTexture(const std::string& fileName);
    void setNormalTexture(const std::string& fileName);
    void setShdrUniform_Texture(const std::string& name, stUint id, stUint index);
    void setShdrUniform_Texture2DArray(const std::string& name, stUint id, stUint index);

    void setShdrUniform(const std::string& name, int value);
    void setShdrUniform(const std::string& name, float value);
    void setShdrUniform(const std::string& name, Vector2<stReal> value);
    void setShdrUniform(const std::string& name, Vector3<stReal> value);
    void setShdrUniform(const std::string& name, Vector4<stReal> value);
    void setShdrUniform(const std::string& name, Matrix4f value);
    void setShdrUniform_Texture(const std::string& name, stUint value);
    void setShdrUniform_CubeMap(const std::string& name, stUint value);
    std::shared_ptr<STMaterial> GetMaterial(){ return m_Material; }

    inline STMaterial* getMaterial(){ return m_Material.get(); }

    void update() override;
    void draw() override;
    void dispose() override;

    void save(std::ofstream& out) override;
    void load(std::ifstream& in) override;

    std::map<std::string, STShader::ShaderAttrib> &GetUniforms();

    void draw(Transform& T, Camera& C);
private:
    std::shared_ptr<STMaterial> m_Material;
    std::map<std::string, STShader::ShaderAttrib> m_Uniforms;
};
#endif //WAHOO_STGRAPHICSCOMPONENT_H
