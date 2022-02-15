#pragma once

#include "States/GameState.h"
 
class Game
{
private:
    // Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;

    // Delta time
    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    // Initializations
    void initWindow();
    void initStates();

public:
    
    // Constructor/Destructor 
    Game();
    virtual ~Game();

    // Funcions
    void updateDt();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};