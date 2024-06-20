#include "canvas.hpp"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <queue>
#include "Engine/Point.hpp"
#include "UI/Component/ImageButton.hpp" // Include the header file for Engine::ImageButton

canvas::canvas() {
    std::cout<<"creating canvas"<<std::endl;
    this->visible = true;
    this->paint_brush_size = 1;
    canvasBitmap = al_create_bitmap(canvasWidth, canvasHeight);
    al_set_target_bitmap(canvasBitmap);
    al_clear_to_color(al_map_rgb(0, 255, 255)); // Initialize with a default color
    al_set_target_backbuffer(al_get_current_display()); // Reset target to backbuffer
}
bool color_compare(ALLEGRO_BITMAP *a, ALLEGRO_COLOR b,int x,int y){
    return al_get_pixel(a,x,y).r == b.r 
    && al_get_pixel(a,x,y).g == b.g 
    && al_get_pixel(a,x,y).b == b.b;
}
void canvas::OnMouseDown(int button, int mx, int my) {
    if (button == 1) {
        if(mouseIn){
            isMousePressed = true;
        }
    }
    if(bucket_switch){
        //bfs to fill the enclosed area
        int canvasX = mx/2;
        int canvasY = my/2;
        al_set_target_bitmap(canvasBitmap);
        ALLEGRO_COLOR boundary_color = al_map_rgb(0, 255, 255);
        ALLEGRO_COLOR fill_color = al_map_rgb(0, 0, 0);
        std::queue<std::pair<int, int>> q;
        q.push({canvasX, canvasY});
        while(!q.empty()){
            auto t = q.front();
            int x = t.first, y = t.second;
            q.pop();
            if(x < 0 || x >= canvasWidth || y < 0 || y >= canvasHeight) continue;
            if(color_compare(canvasBitmap,boundary_color,x,y)) continue;
            al_draw_pixel(canvasX, canvasY, fill_color);
            al_set_target_backbuffer(al_get_current_display());
            q.push({x+1, y});
            q.push({x-1, y});
            q.push({x, y+1});
            q.push({x, y-1});
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
            std::cout<<"brush size is "<<brush_size<<std::endl;
            al_set_target_bitmap(canvasBitmap);
            for (int offsetY = -brush_size/2; offsetY <= brush_size/2; ++offsetY) {
                for (int offsetX = -brush_size/2; offsetX <= brush_size/2; ++offsetX) {
                    int paintX = canvasX + offsetX;
                    int paintY = canvasY + offsetY;
                    // Ensure the paint position is within the canvas bounds
                    if (paintX >= 0 && paintX < canvasWidth && paintY >= 0 && paintY < canvasHeight) {
                        // Set the pixel color to black
                        if(eraser_switch==0)al_draw_pixel(paintX, paintY, al_map_rgb(0, 0, 0));
                        else al_draw_pixel(paintX, paintY, al_map_rgb(0, 255, 255));
                        al_set_target_backbuffer(al_get_current_display());
                    }
                }
            }
        }
    } else {
        mouseIn = false;
    }
}
void canvas::Draw() const {
    al_draw_scaled_bitmap(canvasBitmap,
                          0, 0, canvasWidth, canvasHeight, // source bitmap region
                          0, 0, 2 * canvasWidth, 2 * canvasHeight, // target display region
                          0); // flags
}
void canvas::setBrushSize(int size){
    this->paint_brush_size = size;
    std::cout<<"now paint brush size is "<<paint_brush_size<<std::endl;
}
int canvas::getBrushSize() const{
    return this->paint_brush_size;
}
canvas::~canvas() {
    if (canvasBitmap) {
        al_destroy_bitmap(canvasBitmap);
    }
}