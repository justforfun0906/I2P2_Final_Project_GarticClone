#ifndef PLAYSCENE_HPP
#define PLAYSCENE_HPP
#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include <vector>

class PlayScene final : public Engine::IScene {
private:
	std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    bool isMousePressed = false;
    std::vector<std::vector<ALLEGRO_COLOR>> canvas;
    const int canvasWidth = 800; // Example width
    const int canvasHeight = 600; // Example heigh
    
public:
	explicit PlayScene();
	void Initialize() override;
	void Terminate() override;
	void BackOnClick();
    void Draw() const override;
    void OnMouseDown(int button, int mx, int my);
};

#endif // STAGESELECTSCENE_HPP
