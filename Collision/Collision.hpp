#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <raylib.h>

#include "../Player/Player.hpp"
#include "../World/World.hpp"

class Collision {
   public:
    // Handle collision between two players
    static void HandlePlayerCollision(Player& player1, Player& player2, const World& world);

    // Check if a player's attack hitbox collides with another player
    // static bool CheckAttackCollision(const Player& attacker, const Player& target);
};

#endif
