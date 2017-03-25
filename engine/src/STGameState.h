#ifndef WAHOO_SGAMESTATE_H
#define WAHOO_SGAMESTATE_H

#include "STGame.h"

class STGame;

class STGameState {
public:
    STGameState();
    STGameState(int id);
    virtual ~STGameState();
    int getID(){ return m_id; }

    virtual void init(STGame *) = 0; // Initialize game relevant assets here
    virtual void update(STGame*, stUint) = 0;
    virtual void render(STGame *) = 0; // Handle all rendering here.
protected:
    int m_id;
};


#endif //WAHOO_SGAMESTATE_H
