#ifndef WAHOO_STECHGRAPHICS_H
#define WAHOO_STECHGRAPHICS_H

#include "../STechGlobal.h"

class Camera;
class STechWindow;

class STechGraphics {
public:
    STechGraphics();
    STechGraphics(STechWindow*);
    ~STechGraphics();

    void setCamera(Camera* cam){
        m_Cam = cam;
    }

    Camera* camera(){
        return m_Cam;
    }
private:
    unsigned int WIDTH, HEIGHT;
    Camera* m_Cam;
};


#endif //WAHOO_STECHGRAPHICS_H
