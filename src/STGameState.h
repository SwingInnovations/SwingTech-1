#ifndef WAHOO_SGAMESTATE_H
#define WAHOO_SGAMESTATE_H

#include "../ext/SDL2/SDL_stdinc.h"
#include "STGame.h"

class STGame;

class STGameState {
public:
    STGameState();
    STGameState(int id);
    virtual ~STGameState();
    int getID(){ return m_id; }

    virtual void init(STGame *) = 0; // Initialize game relevant assets here
    virtual void handleInput(STGame *, Uint32) = 0;// Handle all user input here
    virtual void handleLogic(STGame *, Uint32) = 0;//  Handle all game logic in here
    virtual void render(STGame *) = 0; // Handle all rendering here.
protected:
    int m_id;
};


#endif //WAHOO_SGAMESTATE_H
