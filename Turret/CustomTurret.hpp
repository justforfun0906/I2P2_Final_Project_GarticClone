#ifndef CUSTOMTURRET_HPP
#define CUSTOMTURRET_HPP
#include "Turret.hpp"

class CustomTurret: public Turret {
public:
	static const int Price;
    CustomTurret(float x, float y);
	void CreateBullet() override;
};
#endif // CUSTOMTURRET_HPP
