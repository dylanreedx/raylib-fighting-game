#include "./Collision.hpp"

#include <cmath>

void Collision::HandlePlayerCollision(Player& player1, Player& player2, const World& world) {
    // Check if players are colliding
    bool isColliding =
        player1.position.x < player2.position.x + player2.size &&
        player1.position.x + player1.size > player2.position.x &&
        player1.position.y < player2.position.y + player2.size &&
        player1.position.y + player1.size > player2.position.y;

    if (isColliding) {
        // Calculate overlap on each axis
        float overlapX = (player1.size + player2.size) / 2.0f -
                         abs(player1.position.x - player2.position.x);
        float overlapY = (player1.size + player2.size) / 2.0f -
                         abs(player1.position.y - player2.position.y);

        // Resolve collision based on the axis of least penetration
        if (overlapX < overlapY) {
            // Horizontal collision
            if (player1.position.x < player2.position.x) {
                player1.position.x -= overlapX / 2.0f;
                player2.position.x += overlapX / 2.0f;
            } else {
                player1.position.x += overlapX / 2.0f;
                player2.position.x -= overlapX / 2.0f;
            }
        } else {
            // Vertical collision
            if (player1.position.y < player2.position.y) {
                player1.position.y -= overlapY / 2.0f;
                player2.position.y += overlapY / 2.0f;

                // Prevent Player 2 from sinking below the floor
                if (player2.position.y + player2.size > world.floorY) {
                    player2.position.y = world.floorY - player2.size;
                }
            } else {
                player1.position.y += overlapY / 2.0f;
                player2.position.y -= overlapY / 2.0f;

                // Prevent Player 1 from sinking below the floor
                if (player1.position.y + player1.size > world.floorY) {
                    player1.position.y = world.floorY - player1.size;
                }
            }
        }
    }
}

// bool CollisionManager::CheckAttackCollision(const Player& attacker, const Player& target) {
//     return CheckCollisionRecs(attacker.punchHitbox,
//                               {target.position.x, target.position.y, target.size, target.size});
// }
