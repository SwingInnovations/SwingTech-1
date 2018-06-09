#ifndef SWINGTECH1_STRENDERER_H
#define SWINGTECH1_STRENDERER_H

#include "../Entity/STEntity.h"

#if PC
#if GL_RENDERER
    //TODO Implement Redefines for things.
#elif VK_RENDERER

#elif DX_RENDERER

#endif
#endif

class STRenderer {
public:
    //Render Entity Proxy
    class IRenderProxy {
    public:
        explicit IRenderProxy(STEntity* entity){
            m_entity = (void*)entity;   //Store the render entity
        }

        virtual void draw(STRenderer* renderer) = 0;

        /**
         * Gets the stored entity Pointer
         * @return Entity Pointer
         */
        void* getEntityPointer(){ return m_entity; }
    protected:
        void* m_entity;
    };

    explicit STRenderer(STGame* win);

    virtual void init() = 0;


    /**
     * Enables Effects
     * @param effects
     */
    void enabledEffects(const stUint effects);

    /**
     * Disables the particular effect
     * @param effects
     */
    void disableEffects(const stUint effects);

protected:
    Vector2D    m_windowSize;
    stUint      m_enabledEffects = 0x00000000;
};


#endif //SWINGTECH1_STRENDERER_H
