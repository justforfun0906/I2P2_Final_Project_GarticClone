#include <algorithm>
#include <string>

#include "Engine/Point.hpp"
#include "Slider.hpp"
#include <iostream>
Slider::Slider(float x, float y, float w, float h) :
	ImageButton("stage-select/slider.png", "stage-select/slider-blue.png", "stage-select/slider-blue.png",x, y),
	Bar("stage-select/bar.png", x, y, w, h),
	End1("stage-select/end.png", x, y + h / 2, 0, 0, 0.5, 0.5),
	End2("stage-select/end.png", x + w, y + h / 2, 0, 0, 0.5, 0.5) {
	//Position.x += w;
	//Position.y += h / 2;
	Anchor = Engine::Point(0.5, 0.5);
}
void Slider::Draw() const {
    // TODO: [HACKATHON-3-BUG] (4/5): Draw the nested components here, so they are displayed correctly
	Bar.Draw();
	End1.Draw();
	End2.Draw();
	ImageButton::Draw();
}
void Slider::SetOnValueChangedCallback(std::function<void(float value)> onValueChangedCallback) {
	OnValueChangedCallback = onValueChangedCallback;
}
void Slider::SetValue(float value) {
    if (this->value != value) {
        this->value = value; // Store the new value

        // Calculate the new x position for the knob
        float newPositionX = End1.Position.x + value * Bar.Size.x;

        // Update the knob's position
        Position.x = newPositionX;

        // Adjust the knob's position to be centered on the calculated point
        // Assuming the knob's anchor point is at its center
        ImageButton::Position.x = newPositionX;

        if (OnValueChangedCallback)
            OnValueChangedCallback(value);
    }
}
void Slider::OnMouseDown(int button, int mx, int my) {
	if ((button & 1) && mouseIn){
		Down = true;
		std::cout<<"Down"<<std::endl;
	}
}
void Slider::OnMouseUp(int button, int mx, int my) {
	Down = false;
}
void Slider::OnMouseMove(int mx, int my) {
	ImageButton::OnMouseMove(mx, my);
	if (Down) {
		// Clamp
		float clamped = std::min(std::max(static_cast<float>(mx), Bar.Position.x), Bar.Position.x + Bar.Size.x);
		float value = (clamped - Bar.Position.x) / Bar.Size.x * 1.0f;
		SetValue(value);
	}
}
