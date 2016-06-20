#ifndef WAHOO_STLABEL_H
#define WAHOO_STLABEL_H

#include "STInterWidget.h"
#include "../../Math/STCore.h"

class STLabel : public STInterWidget {
public:
    STLabel();
    STLabel(stReal x, stReal y, stReal width, stReal height);


    virtual void update(STGame *window) override;
};


#endif //WAHOO_STLABEL_H
