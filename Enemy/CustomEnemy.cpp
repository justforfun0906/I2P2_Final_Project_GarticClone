#include <string>

#include "CustomEnemy.hpp"

CustomEnemy::CustomEnemy(int x, int y) : Enemy("play/enemy-6.png", x, y, 10, 50, 50, 100) {
	// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'SoldierEnemy.hpp', 'SoldierEnemy.cpp' to create a new enemy.
}
void CustomEnemy::Update(float deltaTime) {
	Enemy::Update(deltaTime);
	float baseSpeed = 50.0f;

    // Define a multiplier that increases as HP decreases
    float speedMultiplier = 1.0f + (50.0f - hp) / 50.0f;

    // Update speed
    speed = baseSpeed * speedMultiplier;
}