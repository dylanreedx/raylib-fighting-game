#include <raylib.h>

#include <cmath>  // For sqrtf

#include "./Follower/Follower.hpp"
#include "./Player/Player.hpp"
#include "./World/World.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Follower Implementation");

    // Create World
    World world(screenWidth, screenHeight);

    // Create Players
    Player player1({100, world.floorY - 25});
    Player player2({screenWidth - 200, world.floorY - 25});

    // Create Follower
    Follower follower({player1.position.x, player1.position.y});

    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update logic
        player1.Update(world, deltaTime);  // Update Player 1
        // Player 2 remains static (no Update call)

        // Handle Collision Between Player 1 and Player 2
        bool isColliding =
            player1.position.x < player2.position.x + player2.size &&
            player1.position.x + player1.size > player2.position.x &&
            player1.position.y < player2.position.y + player2.size &&
            player1.position.y + player1.size > player2.position.y;

        if (isColliding) {
            Vector2 collisionDirection = {
                player1.position.x - player2.position.x,
                player1.position.y - player2.position.y};

            // Normalize the direction vector
            float collisionMagnitude = sqrtf(collisionDirection.x * collisionDirection.x +
                                             collisionDirection.y * collisionDirection.y);
            if (collisionMagnitude != 0) {
                collisionDirection.x /= collisionMagnitude;
                collisionDirection.y /= collisionMagnitude;

                float overlap = player1.size - collisionMagnitude;
                if (overlap < 0) overlap = 0;  // Avoid negative overlap

                // Apply a small push to separate the players
                float pushStrength = overlap + 1.0f;
                player1.position.x += collisionDirection.x * pushStrength;
                player1.position.y += collisionDirection.y * pushStrength;

                player2.position.x -= collisionDirection.x * pushStrength;
                player2.position.y -= collisionDirection.y * pushStrength;
            }
        }

        // Update follower position
        follower.Update(player1, player2);

        // Draw everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        world.Draw();     // Draw the world
        player1.Draw();   // Draw Player 1
        player2.Draw();   // Draw Player 2
        follower.Draw();  // Draw the follower

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
