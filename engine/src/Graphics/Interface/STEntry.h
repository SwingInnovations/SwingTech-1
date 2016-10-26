#ifndef SWINGTECH1_STENTRY_H
#define SWINGTECH1_STENTRY_H

#include "STInterWidget.h"
#include "STPanel.h"

class STEntry : public STInterWidget {
public:
    STEntry();

    void update(STGame* window);

    inline void setDefaultText(const std::string& text) {
        m_defaultText = text;
    }

    void draw(STGraphics* g);
private:
    std::string m_defaultText;
    bool m_inFocus;
    STPanel* m_panel;
};


#endif //SWINGTECH1_STENTRY_H
