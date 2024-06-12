#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy/Enemy.hpp"
#include "FireBullet.hpp"
#include "CustomBullet.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Turret;

CustomBullet::CustomBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
	Bullet("play/bullet-7.png", 1000, 2, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
	// TODO: [CUSTOM-TOOL] You can imitate the 2 files: 'FireBullet.hpp', 'FireBullet.cpp' to create a new bullet.
}
void CustomBullet::OnExplode(Enemy* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0.5, 1);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/explosion-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
	enemy->SetSpeed(enemy->GetSpeed() * 0.2);
}

