#include "Game.h"

// Static Functions

// Initializer Functions

/**
 * @brief Creates a SFML window
 * @return void
 */
void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");

    std::string title = "None";
    sf::VideoMode window_bounds(800, 600);
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
    }

    ifs.close();

    this->window = new sf::RenderWindow(window_bounds, title);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
    this->states.push(new GameState(this->window)); // Game state
}

// Constructors/Destructors
Game::Game()
{
    this->initWindow();
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

/**
 * @brief Updates the dt variable with the time it takes to update and render one frame
 * 
 */
void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();

    system("cls");

    std::cout << this->dt << std::endl;
}

// Functions
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