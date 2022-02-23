#include "Button.h"

Button::Button(float x, float y, 
            float width, float height, 
            sf::Font* font, std::string text, unsigned character_size,
            sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
            sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
    this->butotonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(this->idleColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(text_idle_color);
    this->text.setCharacterSize(character_size);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;
}

Button::~Button()
{

}

const bool Button::isPressed() const
{
    return this->butotonState == BTN_ACTIVE;
}

/**
 * @brief Update the bolleans for hover and pressed
 * 
 * @param mousePos 
 */
void Button::update(const sf::Vector2f mousePos)
{
    // Idle
    this->butotonState = BTN_IDLE;

    // Hover
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->butotonState = BTN_HOVER;

        // Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->butotonState = BTN_ACTIVE;
        }
    }

    switch (this->butotonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->text.setFillColor(this->textIdleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    default:
        this->shape.setFillColor(sf::Color::Red);
        this->text.setFillColor(sf::Color::Blue);
        break;
    }

}

void Button::render(sf::RenderTarget& target)
{
    target.draw(this->shape);

    target.draw(this->text);
}