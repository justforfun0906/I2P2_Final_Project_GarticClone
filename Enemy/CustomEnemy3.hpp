#ifndef CUSTOMENEMY3_HPP
#define CUSTOMENEMY3_HPP
#include "Enemy.hpp"

class CustomEnemy3 : public Enemy {
public:
	CustomEnemy3(int x, int y);
	void Update(float deltaTime) override;
};
#endif // SOLDIERENEMY_HPP
