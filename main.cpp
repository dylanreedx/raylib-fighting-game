#include <raylib.h>

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int playerSize = 25;

    InitWindow(screenWidth, screenHeight, "Raylib - Physics Simulation");

    const float playerSpeed = 600.0f;        // Horizontal speed
    const float gravity = 1000.0f;           // Pixels per second squared
    const float floorY = screenHeight - 50;  // Y-coordinate of the floor
    const float jumpVelocity = -200.0f;      // Jump velocity
    const float friction = 0.85f;            // Friction factor for horizontal movement
    const float airFriction = 0.989f;        // Reduced friction while in the air
    const float bounceFactor = 0.5f;         // Bounce factor when hitting walls

    Vector2 playerPosition = {screenWidth / 2 - playerSize / 2, floorY - playerSize};
    Vector2 playerVelocity = {0, 0};  // Velocity for X and Y
    bool onGround = true;             // Whether the player is on the ground
    bool canDash = false;

    SetTargetFPS(120);  // Set the desired FPS

    // Main game loop
    while (!WindowShouldClose()) {  // Detect if the window should close
        float deltaTime = GetFrameTime();

        // Handle input (apply horizontal velocity)
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
            canDash = false;
        }

        // Apply gravity
        if (!onGround) {
            playerVelocity.y += gravity * deltaTime;
        }

        if (IsKeyPressed(KEY_SPACE) && !onGround) {
            canDash = true;
            if (canDash) {
                // shoot player in the direction they are facing at a high speed
                if (playerVelocity.x > 0) {
                    playerVelocity.x = playerSpeed * 2;
                } else if (playerVelocity.x < 0) {
                    playerVelocity.x = -playerSpeed * 2;
                }
            }
        }

        // Update position based on velocity
        playerPosition.x += playerVelocity.x * deltaTime;
        playerPosition.y += playerVelocity.y * deltaTime;

        // Check collision with the floor
        if (playerPosition.y + playerSize >= floorY) {
            playerPosition.y = floorY - playerSize;  // Snap to the floor
            playerVelocity.y = 0;                    // Reset vertical velocity
            onGround = true;                         // Mark player as on the ground
        }

        // Keep player within screen bounds and slightly bounce and keep velocity when hitting walls
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
        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("WASD to move, SPACE to jump!", 10, 10, 20, DARKGRAY);
        DrawRectangleV(playerPosition, {playerSize, playerSize}, BLUE);
        DrawRectangle(0, floorY, screenWidth, screenHeight - floorY, DARKGRAY);  // Draw the floor
        DrawFPS(10, 40);
        EndDrawing();
    }

    // Cleanup and exit
    CloseWindow();  // Close window and OpenGL context

    return 0;
}
