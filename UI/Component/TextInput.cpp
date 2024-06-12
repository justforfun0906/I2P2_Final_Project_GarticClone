  // namespace Engine
#include <allegro5/allegro_font.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Label.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/TextInput.hpp"

namespace Engine {
    TextInput::TextInput(std::string text, std::string font, float fontSize, float x, float y, float w, float h)
        : Label(text, font, fontSize, x, y, 255, 255, 255, 255, 0, 0), text(std::move(text)), font(std::move(font)), fontSize(fontSize), x(x), y(y), w(w), h(h), focus(false) {
        // Initialize the TextInput component   
    }

    void TextInput::OnKeyDown(int keyCode) {
    if(text == "Enter_your_name") {
        text = "";
    }
    if (keyCode >= ALLEGRO_KEY_A && keyCode <= ALLEGRO_KEY_Z) {
        // Convert A-Z key codes to lowercase characters
        text += 'a' + (keyCode - ALLEGRO_KEY_A);
    } else if (keyCode >= ALLEGRO_KEY_0 && keyCode <= ALLEGRO_KEY_9) {
        // Convert 0-9 key codes to characters
        text += '0' + (keyCode - ALLEGRO_KEY_0);
    } else if (keyCode == ALLEGRO_KEY_SPACE) {
        // Handle space key code
        text += ' ';
    } else if (keyCode == ALLEGRO_KEY_BACKSPACE && !text.empty()) {
        // Handle backspace key code
        text.pop_back();
    }
    // Trigger the callback if it's set
    if (onValueChanged) {
        onValueChanged();
    }
    }

    void TextInput::Draw() const {
        al_draw_text(Resources::GetInstance().GetFont(font, fontSize).get(), al_map_rgb(255, 255, 255), x, y, 0, text.c_str());
        // Draw the TextInput component on the screen
    }

    std::string TextInput::GetText() const {
        return text;
    }

}