#include "Player.h"

// Constructors/Destructors
Player::Player(float x, float y, sf::Texture& texture)
{
    this->initVariables();

    this->setPosition(x, y);

    this->createMovementComponent(50.f, 5.f, 3.f);
    this->createAnimationComponent(texture);
    this->createHitboxComponent(8.f, 16.f, 16.f, 32.f);

    this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 3, 0, 48, 48);
    this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 1, 5, 1, 48, 48);
}

Player::~Player()
{
    
}

// Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{

}

void Player::update(const float& dt)
{
    this->movementComponent->update(dt);

    if (this->movementComponent->getState(IDLE)) {
        this->animationComponent->play("IDLE_LEFT", dt);
    } else if (this->movementComponent->getState(MOVING_RIGHT)) {
        this->animationComponent->play("WALK_RIGHT", dt);
    }

    this->hitboxComponent->update();
}