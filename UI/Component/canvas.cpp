#include "canvas.hpp"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include "Engine/Point.hpp"

canvas::canvas() {
    canva.resize(canvasHeight, std::vector<ALLEGRO_COLOR>(canvasWidth, al_map_rgb(255, 255, 255)));
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
            // Ensure the mouse position is within the canvas bounds
            if (canvasX >= 0 && canvasX < canvasWidth && canvasY >= 0 && canvasY < canvasHeight) {
                // Set the pixel color to black
                canva[canvasY][canvasX] = al_map_rgb(0, 0, 0);
            }
        }
    } else {
        mouseIn = false;
    }
}
void canvas::Draw(){
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