#ifndef CUSTOMENEMY_HPP
#define CUSTOMENEMY_HPP
#include "Enemy.hpp"

class CustomEnemy : public Enemy {
public:
	CustomEnemy(int x, int y);
	void Update(float deltaTime) override;
};
#endif // SOLDIERENEMY_HPP
