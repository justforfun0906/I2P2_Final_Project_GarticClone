#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <allegro5/bitmap.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Engine/IControl.hpp"
#include "Engine/IObject.hpp"
#include "Image.hpp"

class canvas : public Engine::IControl  , public Engine::IObject{
private:
    bool visible = true;
    bool isMousePressed = false;
    std::vector<std::vector<ALLEGRO_COLOR>> canva;
    const int canvasWidth = 600; // Example width
    const int canvasHeight = 400; // Example heigh
    bool mouseIn = false;
    int paint_brush_size;
public:
    bool eraser_switch = false;
    canvas();
    void OnMouseDown(int button, int mx, int my) override;
    void OnMouseMove(int mx, int my) override;
    void OnMouseUp(int button, int mx, int my) override;
    void Draw()const override;
    void setBrushSize(int size);
    int getBrushSize() const;
};
#endif