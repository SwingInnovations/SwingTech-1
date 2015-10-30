#ifndef WAHOO_STECHGRAPHICS_H
#define WAHOO_STECHGRAPHICS_H


#include "../STechWindow.h"

class STechGraphics {
    STechGraphics();
    STechGraphics(STechWindow*);
    ~STechGraphics();
private:
    unsigned int WIDTH, HEIGHT;
};


#endif //WAHOO_STECHGRAPHICS_H
