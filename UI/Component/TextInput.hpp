#include "Engine/IControl.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/IObject.hpp"
#include "Label.hpp"
#include <functional>

namespace Engine {
    class IInputHandler {
    public:
        virtual ~IInputHandler() = default;
        virtual void OnKeyDown(int keyCode) = 0;
    };
    class TextInput : public IControl , public IInputHandler, public Label{
    public:
        explicit TextInput();
        explicit TextInput(std::string text, std::string font, float fontSize, float x, float y, float w, float h);
        void OnKeyDown(int keyCode) override;
        void Draw() const override;
        std::string GetText() const;
    private:
        std::string text;
        std::string font;
        float fontSize;
        float x, y, w, h;
        bool focus;
        std::function<void()> onValueChanged;
        std::function<void()> onFocus;
        std::function<void()> onFocusOut;
    };
}