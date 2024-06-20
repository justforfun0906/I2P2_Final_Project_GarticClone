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
    ALLEGRO_BITMAP* canvasBitmap;
    bool visible = true;
    bool isMousePressed = false;
    const int canvasWidth = 1200; // Example width
    const int canvasHeight = 800; // Example heigh
    bool mouseIn = false;
    int paint_brush_size;
public:
    bool eraser_switch = false;
    bool bucket_switch = false;
    canvas();
    ~canvas();
    void OnMouseDown(int button, int mx, int my) override;
    void OnMouseMove(int mx, int my) override;
    void OnMouseUp(int button, int mx, int my) override;
    void Draw()const override;
    void setBrushSize(int size);
    int getBrushSize() const;
};
#endif