#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <raylib.h>

#include "../World/World.hpp"

class Player {
   public:
    Vector2 position;
    Vector2 velocity;
    float size = 25.0f;
    bool onGround = true;
    bool canDash = false;
    float speed = 500.0f;
    float jumpVelocity = -300.0f;
    float friction = 0.9f;
    float airFriction = 0.95f;
    float dashSpeed = 1750.0f;
    float dashCooldown = 1.0f;
    float dashDuration = 0.2f;
    float dashTimer = 0.0f;
    bool isDashing = false;

    Player(Vector2 startPosition);

    // Combat
    bool isPunching = false;
    float punchCooldown = 0.5f;  // Cooldown in seconds
    float punchTimer = 0.0f;
    Rectangle punchHitbox;  // The punch hitbox

    void Update(World& world, float deltaTime);  // Player logic (movement, physics)
    void Attack();
    void Draw();  // Render the player
};

#endif
