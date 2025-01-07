#include "World.hpp"

World::World(float screenWidth, float screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    gravity = 1000.0f;              // Pixels per second squared
    floorY = screenHeight - 50.0f;  // Floor is 50 pixels from the bottom
    worldWidth = screenWidth;       // Match screen width for now
    worldHeight = screenHeight;     // Match screen height for now
}

void World::Draw() {
    // Draw the floor
    DrawRectangle(0, floorY, screenWidth, screenHeight - floorY, DARKGRAY);

    // Add more world elements if needed (e.g., platforms, hazards)
    DrawText("WASD to move Player 1. SPACE to jump/dash. Player 2 is static.", 10, 10, 20, DARKGRAY);

    // Display FPS for debugging
    DrawFPS(10, 40);
}
