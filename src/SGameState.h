#ifndef WAHOO_SGAMESTATE_H
#define WAHOO_SGAMESTATE_H

#include "../ext/SDL2/SDL_stdinc.h"
#include "STechWindow.h"

class STechWindow;

class SGameState {
public:
    SGameState();
    SGameState(int id);
    virtual ~SGameState();
    int getID(){ return m_id; }

    virtual void init(STechWindow*){} // Initialize game relevant assets here
    virtual void handleInput(STechWindow*, Uint32){}// Handle all user input here
    virtual void handleLogic(STechWindow*, Uint32){}//  Handle all game logic in here
    virtual void render(STechWindow*){} // Handle all rendering here.
protected:
    int m_id;
};


#endif //WAHOO_SGAMESTATE_H
