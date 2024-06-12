#include <string>

#include "CustomEnemy2.hpp"

CustomEnemy2::CustomEnemy2(int x, int y) : Enemy("play/enemy-7.png", x, y, 10, 50, 50, 100) {
	// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
}
void CustomEnemy2::Update(float deltaTime) {
	Enemy::Update(deltaTime);
	float baseSpeed = 50.0f;

    // Define a multiplier that increases as HP decreases
    float speedMultiplier = 1.0f + (50.0f - hp) / 50.0f;

    // Update speed
    speed = baseSpeed * speedMultiplier;
}