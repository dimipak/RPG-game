#include "Game.h"

// Static Functions

// Initializer Functions

void Game::initVariables()
{
    this->window = NULL;
    this->fullScreen = false;
    this->dt = 0.f;
}

/**
 * @brief Creates a SFML window
 * @return void
 */
void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();

    this->fullScreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> this->fullScreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->windowSettings.antialiasingLevel = antialiasing_level;

    if (this->fullScreen) {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
    } else {
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
    }
    
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
    // this->suppportedKeys.emplace("Escape", sf::Keyboard::Key::Escape);
    // this->suppportedKeys.emplace("A", sf::Keyboard::Key::A);
    // this->suppportedKeys.emplace("D", sf::Keyboard::Key::D);
    // this->suppportedKeys.emplace("W", sf::Keyboard::Key::W);
    // this->suppportedKeys.emplace("S", sf::Keyboard::Key::S);    

    std::ifstream ifs("config/supported_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;
        while (ifs >> key >> key_value)
        {
            this->suppportedKeys[key] = key_value;
        }
        
    }

    ifs.close();

    // DEBUG REMOVE LATER
    for (auto i : this->suppportedKeys)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->suppportedKeys, &this->states));
}

// Constructors/Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while(!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// Functions
void Game::endApplication()
{
    std::cout << "Ending Application" << std::endl;
}

/**
 * @brief Updates the dt variable with the time it takes to update and render one frame
 * 
 */
void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();

    // system("cls");

    // std::cout << this->dt << std::endl;
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        // "close requested" event: we close the window
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }

}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // Close Applicatino
    else 
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    // clear the window
    this->window->clear();

    // render items
    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    // end the current frame
    this->window->display();
}

void Game::run()
{
    // run the program as long as the window is open
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}