#ifndef WAHOO_STLABEL_H
#define WAHOO_STLABEL_H

#include "STInterWidget.h"
#include "../../Math/STCore.h"

class STLabel : public STInterWidget {
public:
    STLabel();
    STLabel(stReal x, stReal y, std::string& text);
    virtual void update(STGame *window) override;
    void draw(STGraphics* grphx);
private:
    Vector2<stReal> m_position;
};


#endif //WAHOO_STLABEL_H
