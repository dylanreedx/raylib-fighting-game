#include <raylib.h>

#include <cmath>  // For sqrtf

#include "./Collision/Collision.hpp"
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

    // Main game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update Players
        player1.Update(world, deltaTime);
        follower.Update(player1, player2);

        // Handle collision between Player 1 and Player 2
        Collision::HandlePlayerCollision(player1, player2, world);

        // Allow Player 1 to attack continuously with KEY_E
        if (IsKeyDown(KEY_E)) {
            player1.Attack();
        }

        // // Check if Player 1's attack hits Player 2
        // if (CollisionManager::CheckAttackCollision(player1, player2)) {
        //     DrawText("HIT!", 400, 300, 20, RED);  // Debug feedback for successful hit
        // }

        // Draw Everything
        BeginDrawing();
        ClearBackground(RAYWHITE);

        world.Draw();
        player1.Draw();
        follower.Draw();
        player2.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
