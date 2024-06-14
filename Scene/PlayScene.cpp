#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_primitives.h> // Add this line to include the necessary header file for al_draw_line
#include <functional>
#include <memory>
#include <string>
#include <iostream>
#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "PlayScene.hpp"
PlayScene::PlayScene() {
    canvas.resize(canvasHeight, std::vector<ALLEGRO_COLOR>(canvasWidth, al_map_rgb(255, 255, 255))); // White background
    // Other initialization...
}
void PlayScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    Engine::ImageButton* btn;
    // Adjust the y-coordinate to place the button 100 pixels from the bottom of the screen
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, h - 100 - 100, 400, 100);
    btn->SetOnClickCallback(std::bind(&PlayScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, h - 100 - 50, 0, 0, 0, 255, 0.5, 0.5));
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void PlayScene::Terminate() {
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void PlayScene::BackOnClick() {
    std::cout<<"BackOnClick"<<std::endl;
    Engine::GameEngine::GetInstance().ChangeScene("start");
}
void PlayScene::OnMouseDown(int button, int mx, int my) {
    std::cout<<"Mouse Down"<<std::endl;
    if (button & 1) { // Left mouse button
        if (mx >= 0 && mx < canvasWidth && my >= 0 && my < canvasHeight) {
            for (int i = -2; i <= 2; ++i) {
                for (int j = -2; j <= 2; ++j) {
                    int px = mx + j;
                    int py = my + i;
                    if (px >= 0 && px < canvasWidth && py >= 0 && py < canvasHeight) {
                        canvas[py][px] = al_map_rgb(0, 0, 0); // Change pixel color to black
                    }
                }
            }
        }
    }
}

void PlayScene::Draw() const {
    al_clear_to_color(al_map_rgb(255, 255, 255)); // Clear background
    for (int y = 0; y < canvasHeight; ++y) {
        for (int x = 0; x < canvasWidth; ++x) {
            al_draw_pixel(x, y, canvas[y][x]);
        }
    }
    Group::Draw(); // Draw other scene elements
}