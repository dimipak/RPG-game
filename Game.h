#pragma once

#include "States/MainMenuState.h"
 
class Game
{
private:
    // Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullScreen;

    // Delta time
    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    std::map<std::string, int> suppportedKeys;

    // Initializations
    void initVariables();
    void initWindow();
    void initStates();
    void initKeys();

public:
    
    // Constructor/Destructor 
    Game();
    virtual ~Game();

    // Funcions

    // Regular
    void endApplication();

    // Update
    void updateDt();
    void updateSFMLEvents();
    void update();

    // Render
    void render();

    // Core
    void run();
};