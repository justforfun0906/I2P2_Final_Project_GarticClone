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
#include "UI/Component/canvas.hpp"
#include "PlayScene.hpp"
canvas* canva = new canvas();
void PlayScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;   
    al_clear_to_color(al_map_rgb(0, 0, 0));
    // Adjust the y-coordinate to place the button 100 pixels from the bottom of the screen
    canvas* canva = new canvas();
    AddNewControlObject(canva);
    Slider* pen_brush = new Slider(w - 240, 40, 190, 4);
    AddNewControlObject(pen_brush);
    // Modify the existing line in PlayScene::Initialize
    pen_brush->SetOnValueChangedCallback(
        std::bind(&PlayScene::PaintBrushSizeChanged, this, std::placeholders::_1));
    pen_brush->SetValue(0);
    // Not safe if release resource while playing, however we only free while change scene, so it's fine.
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
}
void PlayScene::OnKeyDown(int keyCode) {
    if (keyCode == ALLEGRO_KEY_ESCAPE) {
        // Log the action for debugging purposes
        std::cout << "ESC pressed, going back to start scene." << std::endl;
        // Change to the start scene
        Engine::GameEngine::GetInstance().ChangeScene("start");
    }
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
void PlayScene::PaintBrushSizeChanged(float value){
    float temp = 10*value;
    canva->setBrushSize(1+(int)temp);
}
/*void PlayScene::Draw(){
    Group::Draw();
}*/