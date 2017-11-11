#ifndef WAHOO_SGAMESTATE_H
#define WAHOO_SGAMESTATE_H

#include "STGame.h"

class STGame;
class STScene;

class STGameState {
public:
    STGameState();
    STGameState(int id) ;
    virtual ~STGameState();
    int getID(){ return m_id; }
    void init_Internal(STGame* rootGame);

    virtual void init(STGame *) = 0; // Initialize game relevant assets here
    virtual void update(STGame*) = 0;
    virtual void render(STGame *) = 0; // Handle all rendering here.
protected:
    //Intended to act as a sleeper for the scene.
    void restore();
    void sleep();
    int m_id;
    std::string scenePath;  // This is where the binary data of a scene is saved.
    bool m_isRestored = false;
    STScene* m_scene;
};


#endif //WAHOO_SGAMESTATE_H
