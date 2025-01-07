#include <raylib.h>

#include <cmath>  // For sqrtf, sin, and cos

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int playerSize = 25;
    const int followerSize = 10;

    InitWindow(screenWidth, screenHeight, "Raylib - Adjusted Follower Position");

    // Player 1 settings
    const float playerSpeed = 600.0f;        // Horizontal speed
    const float gravity = 1000.0f;           // Pixels per second squared
    const float floorY = screenHeight - 50;  // Y-coordinate of the floor
    const float jumpVelocity = -300.0f;      // Jump velocity
    const float friction = 0.85f;            // Friction factor for horizontal movement
    const float airFriction = 0.98f;         // Reduced friction while in the air
    const float bounceFactor = 0.5f;         // Bounce factor when hitting walls

    Vector2 playerPosition = {100, floorY - playerSize};
    Vector2 playerVelocity = {0, 0};
    bool onGround = true;
    bool canDash = false;

    // Player 2 (anchor) settings
    Vector2 player2Position = {screenWidth - 200, floorY - playerSize};

    // Follower settings
    const float maxFollowerDistance = 50.0f;  // Max distance between Player 1 and the Follower
    Vector2 followerPosition = {playerPosition.x, playerPosition.y};

    SetTargetFPS(120);  // Set the desired FPS

    // Main game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Player 1 (movement and physics)
        if (IsKeyDown(KEY_A)) {
            playerVelocity.x = -playerSpeed;
        } else if (IsKeyDown(KEY_D)) {
            playerVelocity.x = playerSpeed;
        } else {
            // Apply friction when no input
            playerVelocity.x *= onGround ? friction : airFriction;
        }

        // Handle jumping
        if (IsKeyPressed(KEY_SPACE) && onGround) {
            playerVelocity.y = jumpVelocity;
            onGround = false;
            canDash = true;
        }

        // Apply gravity to Player 1
        if (!onGround) {
            playerVelocity.y += gravity * deltaTime;
        }

        // Handle dashing in mid-air
        if (IsKeyPressed(KEY_SPACE) && !onGround && canDash) {
            canDash = false;
            if (playerVelocity.x > 0) {
                playerVelocity.x = playerSpeed * 2;  // Dash right
            } else if (playerVelocity.x < 0) {
                playerVelocity.x = -playerSpeed * 2;  // Dash left
            }
        }

        // Update Player 1 position
        playerPosition.x += playerVelocity.x * deltaTime;
        playerPosition.y += playerVelocity.y * deltaTime;

        bool isColliding =
            playerPosition.x < player2Position.x + playerSize &&
            playerPosition.x + playerSize > player2Position.x &&
            playerPosition.y < player2Position.y + playerSize &&
            playerPosition.y + playerSize > player2Position.y;

        if (isColliding) {
            Vector2 collisionDirection = {
                playerPosition.x - player2Position.x,
                playerPosition.y - player2Position.y};

            // Normalize the direction vector
            float collisionMagnitude = sqrtf(collisionDirection.x * collisionDirection.x +
                                             collisionDirection.y * collisionDirection.y);
            if (collisionMagnitude != 0) {
                collisionDirection.x /= collisionMagnitude;
                collisionDirection.y /= collisionMagnitude;

                float overlap = playerSize - collisionMagnitude;
                if (overlap < 0) overlap = 0;  // Avoid negative overlap

                // Apply a small push to separate the players
                float pushStrength = overlap + 1.0f;
                playerPosition.x += collisionDirection.x * pushStrength;
                playerPosition.y += collisionDirection.y * pushStrength;
                player2Position.x -= collisionDirection.x * pushStrength;
                player2Position.y -= collisionDirection.y * pushStrength;
            }
        }

        // Collision with the floor for Player 1
        if (playerPosition.y + playerSize >= floorY) {
            playerPosition.y = floorY - playerSize;  // Snap to the floor
            playerVelocity.y = 0;                    // Reset vertical velocity
            onGround = true;                         // Mark player as on the ground
        }

        // Keep Player 1 within screen bounds and apply bounce effect
        if (playerPosition.x < 0) {
            playerPosition.x = 0;
            playerVelocity.x *= -bounceFactor;
            canDash = true;
        }
        if (playerPosition.x + playerSize > screenWidth) {
            playerPosition.x = screenWidth - playerSize;
            playerVelocity.x *= -bounceFactor;
            canDash = true;
        }

        // Player 2 (anchor) - Static with floor collision
        if (player2Position.y + playerSize >= floorY) {
            player2Position.y = floorY - playerSize;
        }

        // Calculate distance from Player 2 to Player 1
        Vector2 directionToPlayer2 = {
            player2Position.x - playerPosition.x,
            player2Position.y - playerPosition.y};

        float distanceToPlayer2 = sqrtf(directionToPlayer2.x * directionToPlayer2.x +
                                        directionToPlayer2.y * directionToPlayer2.y);

        Vector2 normalizedDirection = {
            directionToPlayer2.x / distanceToPlayer2,
            directionToPlayer2.y / distanceToPlayer2};

        // Dynamically calculate follower distance based on distance to Player 2
        float dynamicFollowerDistance = distanceToPlayer2 / 2.0f;
        if (dynamicFollowerDistance > maxFollowerDistance) {
            dynamicFollowerDistance = maxFollowerDistance;
        }
        if (dynamicFollowerDistance < 10.0f) {  // Add minimum distance
            dynamicFollowerDistance = 10.0f;
        }

        // Adjust follower position based on dynamic distance
        followerPosition.x = playerPosition.x + (normalizedDirection.x * dynamicFollowerDistance);
        followerPosition.y = playerPosition.y + (normalizedDirection.y * dynamicFollowerDistance);

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw Player 1
        DrawRectangleV(playerPosition, {playerSize, playerSize}, BLUE);

        // Draw Player 2 (anchor)
        DrawRectangleV(player2Position, {playerSize, playerSize}, GREEN);

        // Draw Follower
        DrawRectangleV(followerPosition, {followerSize, followerSize}, RED);

        // Draw Floor
        DrawRectangle(0, floorY, screenWidth, screenHeight - floorY, DARKGRAY);

        // Draw instructions and FPS
        DrawText("WASD to move Player 1. SPACE to jump/dash. Player 2 is static.", 10, 10, 20, DARKGRAY);
        DrawFPS(10, 40);

        EndDrawing();
    }

    // Cleanup and exit
    CloseWindow();

    return 0;
}
