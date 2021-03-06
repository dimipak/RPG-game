#include "Entity.h"

Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->movementComponent;
    delete this->animationComponent;
    delete this->hitboxComponent;
}

void Entity::initVariables()
{   
    this->movementComponent = NULL;
    this->animationComponent = NULL;
    this->hitboxComponent = NULL;
}

// Componenet Functions
void Entity::setTexture(sf::Texture& texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponent(float offset_x, float offset_y, float width, float height)
{
    this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

// Functions
void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
    if (this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt);
    }
}

void Entity::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Entity::update(const float& dt)
{
    if (this->movementComponent) this->movementComponent->update(dt);
}

void Entity::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);

    if (this->hitboxComponent) this->hitboxComponent->render(target);
}