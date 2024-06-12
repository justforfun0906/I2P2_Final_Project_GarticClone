#ifndef CUSTOMBULLET_HPP
#define CUSTOMBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
struct Point;
}  // namespace Engine

class CustomBullet : public Bullet {
public:
	explicit CustomBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
	void OnExplode(Enemy* enemy) override;
};
#endif // FIREBULLET_HPP
