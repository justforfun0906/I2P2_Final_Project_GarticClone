#include <functional>
#include <memory>
#include "Engine/Collider.hpp"
#include "Engine/GameEngine.hpp"
#include "Image.hpp"
#include "ImageButton.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	ImageButton::ImageButton(std::string img, std::string imgIn,std::string imgHover, float x, float y, float w, float h, float anchorX, float anchorY) :
		Image(img, x, y, w, h, anchorX, anchorY), imgOut(Resources::GetInstance().GetBitmap(img)),
		imgIn(Resources::GetInstance().GetBitmap(imgIn)),
		imgHover(Resources::GetInstance().GetBitmap(imgHover)) {
		Point mouse = GameEngine::GetInstance().GetMousePosition();
		mouseIn = Collider::IsPointInBitmap(Point((mouse.x - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (mouse.y - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
		if (!mouseIn || !Enabled) bmp = imgOut;
		else bmp = this->imgHover;
	}
	void ImageButton::SetOnClickCallback(std::function<void(void)> onClickCallback) {
    OnClickCallback = [this, onClickCallback]() {
        // Toggle between imgOut and imgIn.
        swap(imgOut, imgIn);
        // Call the original callback function if it exists.
        if (onClickCallback) {
            onClickCallback();
        }
    };
}
	void ImageButton::OnMouseDown(int button, int mx, int my) {
		if ((button & 1) && mouseIn && Enabled) {
			if (OnClickCallback)
				OnClickCallback();
		}
	}
	void ImageButton::OnMouseMove(int mx, int my) {
		mouseIn = Collider::IsPointInBitmap(Point((mx - Position.x) * GetBitmapWidth() / Size.x + Anchor.x * GetBitmapWidth(), (my - Position.y) * GetBitmapHeight() / Size.y + Anchor.y * GetBitmapHeight()), bmp);
		if (!mouseIn || !Enabled) bmp = imgOut;
		else bmp = imgHover;
	}
}
