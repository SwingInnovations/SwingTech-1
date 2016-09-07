#ifndef SWINGTECH1_STENTRY_H
#define SWINGTECH1_STENTRY_H

#include "STInterWidget.h"

class STEntry : public STInterWidget {
public:
    STEntry();

    void update(STGame* window);

    void setDefaultText(const std::string& text);
private:
    std::string defaultText;
    bool m_inFocus;
};


#endif //SWINGTECH1_STENTRY_H
