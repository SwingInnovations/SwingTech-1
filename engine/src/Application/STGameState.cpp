#include "STGameState.h"
#include "STSceneManager.h"

STGameState::STGameState() {
    m_id = 0;
}

STGameState::~STGameState() {

}

STGameState::STGameState(int id) {
    this->m_id = id;
}

/**
 * @brief Writes Scene to file
 */
void STGameState::sleep() {

}

/**
 * @brief Restores Scene from File.
 */
void STGameState::restore() {

}

void STGameState::init_Internal(STGame* rootGame) {
    m_scene = new STScene();
    rootGame->getGraphics()->initScene(m_scene);
}

STScene *STGameState::getScene() {
    return m_scene;
}
