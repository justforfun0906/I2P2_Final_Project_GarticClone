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
#include "cursor.hpp"

class canvas : public Engine::IControl  , public Engine::IObject{
private:
    ALLEGRO_BITMAP* canvasBitmap;
    CursorIcon cursor;
    CursorIcon color_indicator;
    bool visible = true;
    bool isMousePressed = false;
    const int canvasWidth = 600; // Example width
    const int canvasHeight = 400; // Example heigh
    bool mouseIn = false;
    int paint_brush_size;
    ALLEGRO_COLOR paint_brush_color = al_map_rgb(0, 0, 0);
public:
    bool eraser_switch = false;
    bool bucket_switch = false;
    canvas();
    ~canvas();
    void setBrushColor(ALLEGRO_COLOR color);
    void OnMouseDown(int button, int mx, int my) override;
    void OnMouseMove(int mx, int my) override;
    void OnMouseUp(int button, int mx, int my) override;
    void Draw()const override;
    void setBrushSize(int size);
    int getBrushSize() const;
    void Update(float deltaTime) override;
    bool color_compare(ALLEGRO_COLOR b, int x, int y);
    ALLEGRO_BITMAP* getBitmap() const;
};
#endif