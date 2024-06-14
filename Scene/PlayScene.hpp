#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class PlayScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit PlayScene() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick();
    void Draw() const override;
};

#endif // STAGESELECTSCENE_HPP
