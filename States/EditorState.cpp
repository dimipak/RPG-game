#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

EditorState::~EditorState()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Initializer Functions
void EditorState::initVariables()
{

}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/Dosis-light.ttf"))
    {
        throw("ERROR::EDITOR_STATE::COULD NOT LOAD FONT");
    }
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("Config/editorstate_keybinds.ini");

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

void EditorState::initButtons()
{
    
}

void EditorState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
        this->endState();
}

/**
 * @brief Updates all these buttons and handles the functionality
 * 
 */
void EditorState::updateButtons()
{
    for (auto &button : this->buttons)
    {
        button.second->update(this->mousePosView);
    }
}

void EditorState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateInput(dt);

    this->updateButtons();

    // system("clear");
    // std::cout << this->mousePosView.x << " " << this->mousePosView.y << std::endl;
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
    for (auto &button : this->buttons)
    {
        button.second->render(target);
    }
}

void EditorState::render(sf::RenderTarget* target)
{
    this->renderButtons(*target);

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