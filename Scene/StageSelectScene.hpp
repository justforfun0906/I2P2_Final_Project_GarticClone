#ifndef STAGESELECTSCENE_HPP
#define STAGESELECTSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"

class StageSelectScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
	explicit StageSelectScene() = default;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick();
	void PlayOnClick();
};

#endif // STAGESELECTSCENE_HPP
