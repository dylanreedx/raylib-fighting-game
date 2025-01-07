#include "Follower.hpp"

#include <cmath>  // For sqrtf

Follower::Follower(Vector2 startPosition) {
    position = startPosition;
}

void Follower::Update(const Player& player1, const Player& player2) {
    // Calculate direction from Player 2 to Player 1
    Vector2 directionToPlayer2 = {
        player2.position.x - player1.position.x,
        player2.position.y - player1.position.y};

    // Calculate distance
    float distanceToPlayer2 = sqrtf(directionToPlayer2.x * directionToPlayer2.x +
                                    directionToPlayer2.y * directionToPlayer2.y);

    // Normalize the direction vector
    Vector2 normalizedDirection = {
        directionToPlayer2.x / distanceToPlayer2,
        directionToPlayer2.y / distanceToPlayer2};

    // Calculate dynamic follower distance
    float dynamicFollowerDistance = distanceToPlayer2 / 2.0f;
    if (dynamicFollowerDistance > maxDistance) {
        dynamicFollowerDistance = maxDistance;
    }
    if (dynamicFollowerDistance < minDistance) {
        dynamicFollowerDistance = minDistance;
    }

    // Update follower position
    position.x = player1.position.x + (normalizedDirection.x * dynamicFollowerDistance);
    position.y = player1.position.y + (normalizedDirection.y * dynamicFollowerDistance);
}

void Follower::Draw() {
    DrawRectangleV(position, {10.0f, 10.0f}, RED);  // Draw follower as a small red square
}
