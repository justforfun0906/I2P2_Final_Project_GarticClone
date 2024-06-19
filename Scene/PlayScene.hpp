#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include <vector>
#include "UI/Component/canvas.hpp"

class PlayScene final : public Engine::IScene{
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;

public:
	explicit PlayScene() = default;
    void OnKeyDown(int keyCode) override;
	void Initialize() override;
	void Terminate() override;
	void BackOnClick();
    void EraserOnClick();
    void PaintBrushSizeChanged(float value);
    //void Draw() override;
};

#endif // STAGESELECTSCENE_HPP
