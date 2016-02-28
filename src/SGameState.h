#ifndef WAHOO_SGAMESTATE_H
#define WAHOO_SGAMESTATE_H

#include "../ext/SDL2/SDL_stdinc.h"
#include "STGame.h"

class STGame;

class SGameState {
public:
    SGameState();
    SGameState(int id);
    virtual ~SGameState();
    int getID(){ return m_id; }

    virtual void init(STGame *){} // Initialize game relevant assets here
    virtual void handleInput(STGame *, Uint32){}// Handle all user input here
    virtual void handleLogic(STGame *, Uint32){}//  Handle all game logic in here
    virtual void render(STGame *){} // Handle all rendering here.
protected:
    int m_id;
};


#endif //WAHOO_SGAMESTATE_H
