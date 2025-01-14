#include "Player.hpp"

Player::Player(Vector2 startPosition) {
    position = startPosition;
}

void Player::Update(World& world, float deltaTime) {
    // Horizontal movement
    if (IsKeyDown(KEY_A))
        velocity.x = -speed;
    else if (IsKeyDown(KEY_D))
        velocity.x = speed;
    else
        velocity.x *= onGround ? friction : airFriction;  // Smooth deceleration

    // Jumping
    if (IsKeyPressed(KEY_SPACE) && onGround) {
        velocity.y = jumpVelocity;
        onGround = false;
        canDash = true;
        dashTimer = 0.0f;  // Reset dash timer when on ground
    }

    // Dashing
    // dashing is kinda accidentally like bhopping it's kinda cool mechanic?
    // you have to stop moving and allow the velocity to pull you and as you hit the ground you can jump to accelerate speed
    if (IsKeyPressed(KEY_SPACE) && !onGround && canDash) {
        canDash = false;
        isDashing = true;
        dashTimer = dashDuration;  // Start dash timer

        // Set dash velocity
        if (IsKeyDown(KEY_A))
            velocity.x = -dashSpeed;  // Dash left
        else if (IsKeyDown(KEY_D))
            velocity.x = dashSpeed;  // Dash right
        else
            velocity.x = (velocity.x > 0) ? dashSpeed : -dashSpeed;  // Keep current direction
    }

    // Handle dash timer
    if (isDashing) {
        dashTimer -= deltaTime;
        if (dashTimer <= 0.0f) {
            isDashing = false;
        }
    }

    // Update punch timer
    if (punchTimer > 0.0f) {
        punchTimer -= deltaTime;
    } else {
        isPunching = false;
    }

    // Update punch hitbox
    if (isPunching) {
        punchHitbox.x = position.x + (velocity.x >= 0 ? size : -size / 2.0f);  // Extend hitbox in facing direction
        punchHitbox.y = position.y;
    } else {
        punchHitbox = {0, 0, 0, 0};  // Disable hitbox when not punching
    }

    // Gravity
    if (!onGround) velocity.y += world.gravity * deltaTime;

    // Position update
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Keep Player within screen bounds and apply bounce effect
    if (position.x < 0) {
        position.x = 0;
        velocity.x *= -world.bounceFactor;  // Use world.bounceFactor if defined globally
        canDash = true;
    }
    if (position.x + size > world.screenWidth) {
        position.x = world.screenWidth - size;
        velocity.x *= -world.bounceFactor;
        canDash = true;
    }

    // Floor collision
    if (position.y + size >= world.floorY) {
        position.y = world.floorY - size;
        velocity.y = 0;
        onGround = true;
    }
}

void Player::Attack() {
    if (punchTimer <= 0.0f) {  // Allow punching after cooldown
        isPunching = true;
        punchTimer = punchCooldown;  // Reset cooldown timer

        // Set initial hitbox position and size
        punchHitbox = {position.x + (velocity.x >= 0 ? size : -size / 2.0f),
                       position.y,
                       size / 2.0f,
                       size / 2.0f};  // Example punch size
    }
}

void Player::Draw() {
    DrawRectangleV(position, {size, size}, BLUE);

    // Draw punch hitbox for debugging
    if (isPunching) {
        DrawRectangleRec(punchHitbox, RED);
    }
}
