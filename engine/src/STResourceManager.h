#ifndef WAHOO_STRESOURCEMANAGER_H
#define WAHOO_STRESOURCEMANAGER_H

#include <vector>
#include <map>
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/STMaterial.h"
/*! Resource Manager
 *  Holds pointers of Materials/Textures/Shaders for
 *  reusability.
 */
class STResourceManager {
public:
    //! A constructor
    STResourceManager();
    //! A Destructor
    ~STResourceManager();

    //! Adds Shader to Resource Manager
    /*!
     *  Adds Shader to Resource Manager. Persistent
     *  for all Game States.
     *  \param key Key for retrieving Shader;
     *  \param shdr Shader to be added to resource manager
     */
    void addShader(std::string, Shader*);
    //! Adds Texture to Resource Manager
    /*!
     *  Adds Shader to Resource Manager. Persistent
     *  for all Game States.
     *  \param key Key for retrieving Shader;
     *  \param tex Shader to be added to resource manager
     */
    void addTexture(std::string, Texture*);
    //! Adds Material to Resource Manager
    /*!
     *  Adds Shader to Resource Manager. Persistent
     *  for all Game States.
     *  \param key Key for retrieving Shader;
     *  \param mat Shader to be added to resource manager
     */
    void addMaterial(std::string, STMaterial*);

    //! Returns pointer to Shader from Resource Manager
    /*!
     *  Returns pointer to Shader of Key from Resource Manager
     *  \param key Key for Shader
     */
    Shader* getShader(std::string);

    //! Returns pointer to Texture from Resource Manager
    /*!
     *  Returns pointer to Texture of Key from Resource Manager
     *  \param key Key for Texture
     */
    Texture* getTexture(std::string);

    //! Returns pointer to STMaterial from Resource Manager
    /*!
     *  Returns pointer to STMaterial of Key from Resource Manager
     *  \param key Key for STMaterial
     */
    STMaterial* getMaterial(std::string);
private:
    std::map<std::string, Shader*> m_shaders;
    std::map<std::string, Texture*> m_textures;
    std::map<std::string, STMaterial*> m_materials;
};


#endif //WAHOO_STRESOURCEMANAGER_H
