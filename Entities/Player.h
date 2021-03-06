#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
    // Variables

    // Initializer functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, sf::Texture& texture);
    ~Player();

    //Functions

    void update(const float& dt);
};