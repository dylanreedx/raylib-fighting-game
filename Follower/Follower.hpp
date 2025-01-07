#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include <raylib.h>

#include "../Player/Player.hpp"

class Follower {
   public:
    Vector2 position;
    float minDistance = 10.0f;  // Minimum distance from Player 1
    float maxDistance = 50.0f;  // Maximum distance from Player 1

    Follower(Vector2 startPosition);

    void Update(const Player& player1, const Player& player2);
    void Draw();
};

#endif
