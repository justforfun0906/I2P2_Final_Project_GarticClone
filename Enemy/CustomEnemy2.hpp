#ifndef CUSTOMENEMY2_HPP
#define CUSTOMENEMY2_HPP
#include "Enemy.hpp"

class CustomEnemy2 : public Enemy {
public:
	CustomEnemy2(int x, int y);
	void Update(float deltaTime) override;
};
#endif // SOLDIERENEMY_HPP
