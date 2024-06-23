#ifndef CURSOR_HPP
#define CURSOR_HPP
#include <allegro5/bitmap.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "Engine/IObject.hpp"

class CursorIcon : public Engine::IObject{
private:
    std::shared_ptr<ALLEGRO_BITMAP> icon = nullptr;
    float x, y;
public:
    CursorIcon();
    void UpdatePosition(int mx, int my);
    void SetIcon(std::string img);
    void Draw() const override;
};
#endif