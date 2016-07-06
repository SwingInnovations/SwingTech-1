#ifndef SWINGTECH1_STPANEL_H
#define SWINGTECH1_STPANEL_H

#include "STInterWidget.h"

class STPanel : public STInterWidget{
public:
    STPanel();
    STPanel(int, int, int, int);
    void draw(STGraphics* grphx);
private:

};


#endif //SWINGTECH1_STPANEL_H
