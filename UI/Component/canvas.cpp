#include "canvas.hpp"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Engine/Point.hpp"
#include "UI/Component/ImageButton.hpp" // Include the header file for Engine::ImageButton

canvas::canvas() {
    std::cout<<"creating canvas"<<std::endl;
    this->visible = true;
    this->paint_brush_size = 1;
    canva.resize(canvasHeight, std::vector<ALLEGRO_COLOR>(canvasWidth, al_map_rgb(0, 255, 255)));
}
void canvas::OnMouseDown(int button, int mx, int my) {
    if (button == 1) {
        if(mouseIn){
            isMousePressed = true;
        }
    }
}
void canvas::OnMouseUp(int button, int mx, int my) {
    if (button == 1) {
        isMousePressed = false;
    }
}
void canvas::OnMouseMove(int mx, int my){
    if (mx >= 0 && mx < canvasWidth*2 && my >= 0 && my < canvasHeight*2) {
        mouseIn = true;
        if (isMousePressed) {
            // Adjust the mouse position to the canvas coordinate system
            int canvasX = mx/2;
            int canvasY = my/2;
            // Paint a square area based on the brushSize
            int brush_size = getBrushSize();
            for (int offsetY = -brush_size/2; offsetY <= brush_size/2; ++offsetY) {
                for (int offsetX = -brush_size/2; offsetX <= brush_size/2; ++offsetX) {
                    int paintX = canvasX + offsetX;
                    int paintY = canvasY + offsetY;
                    // Ensure the paint position is within the canvas bounds
                    if (paintX >= 0 && paintX < canvasWidth && paintY >= 0 && paintY < canvasHeight) {
                        // Set the pixel color to black
                        if(eraser_switch==0)canva[paintY][paintX] = al_map_rgb(0, 0, 0);
                        else canva[paintY][paintX] = al_map_rgb(0, 255, 255);
                    }
                }
            }
        }
    } else {
        mouseIn = false;
    }
}
void canvas::Draw() const{
    for (int y = 0; y < canvasHeight; ++y) {
        for (int x = 0; x < canvasWidth; ++x) {
            for (int dy = 0; dy < 2; ++dy) {
                for (int dx = 0; dx < 2; ++dx) {
                    al_draw_pixel(2*x + dx, 2*y + dy, canva[y][x]);
                }
            }
        }
    }
}
void canvas::setBrushSize(int size){
    this->paint_brush_size = size;
    std::cout<<"now paint brush size is "<<paint_brush_size<<std::endl;
}
int canvas::getBrushSize() const{
    return this->paint_brush_size;
}