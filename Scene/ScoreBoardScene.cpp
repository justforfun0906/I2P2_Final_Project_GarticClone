#include <functional>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "LoseScene.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "ScoreBoardScene.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

struct Record {
    std::string name;
    int score;
    std::string date;
};
using namespace std;
using namespace Engine;
// Create vectors to hold the records for each stage.
std::vector<Record> stage1Records, stage2Records;
void ScoreBoardScene::showBoard(){
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
int halfW = w / 2;
int halfH = h / 2;
	std::ifstream fin("Resource/scoreboard.txt");
	std::string line="";
while (std::getline(fin, line)) {
    // Process the line.
    if (line.empty()||(line[0]!='1'&&line[0]!='2')) {
        continue;
    }
    std::istringstream iss(line);
    std::string name, week, month, day, time, year;
    int stage, score;
    if (!(iss >> stage >> name >> score >> week >> month >> day >> time >> year)) {
        throw std::runtime_error("Scoreboard file is corrupted");
    }
    std::string date = month + " " + day + " "+time;

    // Store the record in the appropriate vector.
    if (stage == 1) {
        stage1Records.push_back({name, score, date});
    } else if (stage == 2) {
        stage2Records.push_back({name, score, date});
    }
}
// Sort the records in descending order by score.
auto compare = [](const Record& a, const Record& b) { return a.score > b.score; };
std::sort(stage1Records.begin(), stage1Records.end(), compare);
std::sort(stage2Records.begin(), stage2Records.end(), compare);

// Display the top 10 records for each stage.
for (int i = 0; i < 10; i++) {
    if (i < stage1Records.size()) {
        std::string text = stage1Records[i].name + ": " + std::to_string(stage1Records[i].score) + " " + stage1Records[i].date;
        AddNewObject(new Engine::Label(text, "pirulen.ttf", 26, halfW / 2, halfH / 4 + 110 + 50 * i, 255, 255, 255, 255, 0.5, 0.5));
    }
    if (i < stage2Records.size()) {
        std::string text = stage2Records[i].name + ": " + std::to_string(stage2Records[i].score) + " " + stage2Records[i].date;
        AddNewObject(new Engine::Label(text, "pirulen.ttf", 26, halfW + halfW / 2, halfH / 4 + 110 + 50 * i, 255, 255, 255, 255, 0.5, 0.5));
    }
}
    // Close the file.
    fin.close();
}
void ScoreBoardScene::Initialize() {
	// TODO: [HACKATHON-1-SCENE] (1/4): You can imitate the 2 files: 'LoseScene.hpp', 'LoseScene.cpp' to implement your start scene.
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Label("Leader Board", "pirulen.ttf", 48, halfW, halfH / 4 + 10, 255, 255, 255, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label("Stage 1", "pirulen.ttf", 48, halfW / 2, halfH / 4 + 60, 255, 255, 255, 255, 0.5, 0.5));
    AddNewObject(new Engine::Label("Stage 2", "pirulen.ttf", 48, halfW + halfW / 2, halfH / 4 + 60, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	//TODO: change the BGM
	bgmInstance = AudioHelper::PlaySample("select.ogg", true, AudioHelper::BGMVolume);
	// Read from file.
	showBoard();
}
void ScoreBoardScene::Terminate() {
    stage1Records.clear();
    stage2Records.clear();
	AudioHelper::StopSample(bgmInstance);
	bgmInstance = std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE>();
	IScene::Terminate();
}
void ScoreBoardScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("start");
}
