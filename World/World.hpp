#ifndef WORLD_HPP
#define WORLD_HPP

#include <raylib.h>

class World {
   public:
    float gravity;              // Global gravity in pixels/s^2
    float floorY;               // Y-coordinate of the floor
    float worldWidth;           // Width of the playable world
    float worldHeight;          // Height of the playable world
    float screenWidth;          // Width of the screen (for rendering)
    float screenHeight;         // Height of the screen (for rendering)
    float bounceFactor = 0.8f;  // Factor to reduce velocity when bouncing

    World(float screenWidth, float screenHeight);

    void Draw();  // Render the world (e.g., floor, boundaries, environment)
};

#endif
