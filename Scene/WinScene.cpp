#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "ScoreBoardScene.hpp"
//#include "UI/Component/TextInput.hpp"
#include <fstream>
#include <chrono>

void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;

	// Create a TextInput object
    Engine::TextInput* input = new Engine::TextInput("Enter_your_name", "pirulen.ttf", 48, halfW-200, halfH * 3 / 4, 400, 100);
	std::string scoreStr = "Score: " + std::to_string(Engine::GameEngine::remainingMoney); // replace 'score' with your score variable
	Engine::Label* scoreLabel = new Engine::Label(scoreStr, "pirulen.ttf", 48, halfW, halfH / 2, 255, 255, 255, 255, 0.5, 0.5);
	AddNewObject(scoreLabel);

    // Add the TextInput object to the scene
    AddNewControlObject(input);
	//AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 -10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, Engine::GameEngine::stage, std::to_string(Engine::GameEngine::remainingMoney), input, "0"));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
	
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage,std::string score, Engine::TextInput* input, std::string time) {
	// Change to select scene.
	// Get the player's name from the TextInput component
    std::string playerName = input->GetText();
	auto now = std::chrono::system_clock::now();
	std::time_t end_time = std::chrono::system_clock::to_time_t(now);
	std::string timeStr = std::ctime(&end_time);
    // Assume you have the player's score and time stored in variables `playerScore` and `playerTime`
    // You need to replace these with the actual variables or function calls that return these values

    // Open the scoreboard file in append mode
    std::ofstream fout("Resource/scoreboard.txt", std::ios::app);
    if (!fout) {
        throw std::runtime_error("Unable to open scoreboard file");
    }

    // Write the player's name, score, and time to the file
    fout <<stage<< " "<<playerName<<" "<< score << " " << timeStr<<'\n';

    // Close the file
    fout.close();
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
