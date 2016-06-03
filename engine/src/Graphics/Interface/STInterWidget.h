#ifndef WAHOO_STINTERWIDGET_H
#define WAHOO_STINTERWIDGET_H

#include "../../STGame.h"
#include "../../STEntity.h"

class STInterWidget : public STEntity{
public:
    STInterWidget(STGame* parent){

    }

    virtual void keyEvent() = 0;
    virtual void mouseEvent() = 0;
    virtual void clickEvent() = 0;
    virtual void pressEvent() = 0;
    virtual void releaseEvent() = 0;
};

#endif //WAHOO_STINTERWIDGET_H
