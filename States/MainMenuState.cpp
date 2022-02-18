#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Initializer Functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
    this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));

    if (!this->backgroundTexture.loadFromFile("Resources/bg1.png"))
    {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    }

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-light.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";
        while (ifs >> key >> key2)
        {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
        
    }

    ifs.close();
}

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE_BTN"] = new Button(300, 480, 250, 50, &this->font, "New Game", 
        sf::Color(70,70,70,200), 
        sf::Color(150,150,150,200),
        sf::Color(20,20,20,200)
    );

    this->buttons["SETTINGS"] = new Button(300, 580, 250, 50, &this->font, "Settings", 
        sf::Color(100,100,100,200), 
        sf::Color(150,150,150,200),
        sf::Color(20,20,20,200)
    );

    this->buttons["EXIT_STATE_BTN"] = new Button(300, 780, 250, 50, &this->font, "Quit", 
        sf::Color(100,100,100,200), 
        sf::Color(150,150,150,200),
        sf::Color(20,20,20,200)
    );
}

void MainMenuState::updateInput(const float& dt)
{

}

/**
 * @brief Updates all these buttons and handles the functionality
 * 
 */
void MainMenuState::updateButtons()
{
    for (auto &button : this->buttons)
    {
        button.second->update(this->mousePosView);
    }

    if (this->buttons["GAME_STATE_BTN"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    if (this->buttons["EXIT_STATE_BTN"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateButtons();

    // system("clear");
    // std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto &button : this->buttons)
    {
        button.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    target->draw(this->background);

    this->renderButtons(target);

    // Remove later!!!
    // sf::Text mouseText;
    // mouseText.setPosition(this->mousePosView.x, this->mousePosView.y-20);
    // mouseText.setFont(this->font);
    // mouseText.setCharacterSize(12);
    // std::stringstream ss;
    // ss << this->mousePosView.x << " " << this->mousePosView.y;
    // mouseText.setString(ss.str());

    // target->draw(mouseText);
}