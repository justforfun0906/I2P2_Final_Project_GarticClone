#include "cursor.hpp"
#include "Engine/Resources.hpp"
#include <iostream>
CursorIcon::CursorIcon() {}

void CursorIcon::UpdatePosition(int mx, int my) {
    x = mx-20;
    y = my+20;
}

void CursorIcon::SetIcon(std::string img){
    icon = Engine::Resources::GetInstance().GetBitmap(img);
}

void CursorIcon::Draw() const {
    if (icon) {
        al_draw_scaled_bitmap(icon.get(), 0, 0, al_get_bitmap_width(icon.get()), al_get_bitmap_height(icon.get()), x, y, 30, 30, 0);
    }
}
