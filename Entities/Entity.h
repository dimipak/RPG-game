#pragma once

// Standard Libray
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>

// SFML Library
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Entity
{
private:
    void initVariables();
    
protected:
    sf::Texture* texture;
    sf::Sprite* sprite;

    // sf::RectangleShape shape; // placeholder
    float movementSpeed;

public: 
    Entity();
    virtual ~Entity();

    // Component Functions
    void createSprite(sf::Texture* texture);

    // Functions
    virtual void move(const float& dt, const float dir_x, const float dir_y);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);
};