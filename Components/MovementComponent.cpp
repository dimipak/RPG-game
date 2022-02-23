#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration) : 
    sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
    
}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f& MovementComponent::getVelocity() const
{
    return this->velocity;
}

// Functions
const bool MovementComponent::getState(const short unsigned state) const
{
    switch (state)
    {
    case IDLE:
        return this->velocity.x == 0.f && this->velocity.y == 0.f;
        break;
    case MOVING:
        return this->velocity.x != 0.f || this->velocity.y != 0.f;
        break;
    case MOVING_LEFT:
        return this->velocity.x < 0.f;
        break;
    case MOVING_RIGHT:
        return this->velocity.x > 0.f;
        break;
    case MOVING_UP:
        return this->velocity.y > 0.f;
        break;
    case MOVING_DOWN:
        return this->velocity.y < 0.f;
        break;
    default:
        return false;
        break;
    }
}

void MovementComponent::move(const float dir_x, const float dir_y, const float & dt)
{
    // Acceleration
    this->velocity.x += this->acceleration * dir_x;

    this->velocity.y += this->acceleration * dir_y;
}

/**
 * @brief Decelerates the sprite and controls the maximum velocity. Moves the sprite
 * 
 * @param dt 
 */
void MovementComponent::update(const float & dt)
{
    // Deceleration X (postive, negative)
    if (this->velocity.x > 0.f) // Check if player moves to the right
    {
        // Max velocity X positive
        if (this->velocity.x > this->maxVelocity) this->velocity.x = this->maxVelocity;

        // Deceleration velocity X positive
        this->velocity.x -= this->deceleration;
        if (this->velocity.x < 0.f) this->velocity.x = 0.f;
    } 
    else if (this->velocity.x < 0.f) // Check if player moves to the left
    {
        // Max velocity X negative
        if (this->velocity.x < -this->maxVelocity) this->velocity.x = -this->maxVelocity;

        // Deceleration velocity X negative
        this->velocity.x += this->deceleration;
        if (this->velocity.x > 0.f) this->velocity.x = 0.f;
    }

    // Deceleration Y (postive, negative)
    if (this->velocity.y > 0.f) // Check if player moves to the top
    {
        // Max velocity Y positive
        if (this->velocity.y > this->maxVelocity) this->velocity.y = this->maxVelocity;

        // Deceleration velocity Y positive
        this->velocity.y -= this->deceleration;
        if (this->velocity.y < 0.f) this->velocity.y = 0.f;
    } 
    else if (this->velocity.y < 0.f) // Check if player moves to the bottom
    {
        // Max velocity Y negative
        if (this->velocity.y < -this->maxVelocity) this->velocity.y = -this->maxVelocity;

        // Deceleration velocity Y negative
        this->velocity.y += this->deceleration;
        if (this->velocity.y > 0.f) this->velocity.y = 0.f;
    }

    // Final move
    this->sprite.move(this->velocity * dt);
}