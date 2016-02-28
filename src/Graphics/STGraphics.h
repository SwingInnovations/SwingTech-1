#ifndef WAHOO_STECHGRAPHICS_H
#define WAHOO_STECHGRAPHICS_H

#include "../STGlobal.h"

class Camera;
class STGame;

class STGraphics {
public:
    STGraphics();
    STGraphics(STGame *);
    ~STGraphics();

    void setCamera(Camera* cam){
        m_Cam = cam;
    }

    void setXUp(bool val){ m_XUp = val; }

    Camera* camera(){
        return m_Cam;
    }
private:
    unsigned int WIDTH, HEIGHT;
    Camera* m_Cam;
    bool m_XUp;
};


#endif //WAHOO_STECHGRAPHICS_H
