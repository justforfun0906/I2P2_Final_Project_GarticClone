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
bool canvas::color_compare(ALLEGRO_COLOR b, int x, int y) {
    ALLEGRO_COLOR c = al_get_pixel(canvasBitmap, x, y);
    return c.r == b.r && c.g == b.g && c.b == b.b; // Ensure this comparison is valid
}
void canvas::OnMouseDown(int button, int mx, int my) {
    if (button == 1) {
        if(mouseIn){
            isMousePressed = true;
        }
    }
    if(bucket_switch){
        //bfs to fill the enclosed area
        al_set_target_bitmap(canvasBitmap);
        ALLEGRO_COLOR boundary_color = al_map_rgb(0, 255, 255);
        ALLEGRO_COLOR fill_color = al_map_rgb(0, 0, 0);
        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<bool>> visited(canvasWidth, std::vector<bool>(canvasHeight, false));
        q.push({mx/2, my/2});
        while(!q.empty()){
            auto t = q.front();
            int x = t.first, y = t.second;
            q.pop();
            if(visited[x][y]|| x < 0 || x >= canvasWidth || y < 0 || y >= canvasHeight || color_compare(fill_color,x,y)) continue;
            //if(!color_compare(boundary_color,x,y)) continue;
            visited[x][y] = true;
            al_draw_pixel(x, y, fill_color);
            q.push({x+1, y});
            q.push({x-1, y});
            q.push({x, y+1});
            q.push({x, y-1});
            
            // Add an exit condition to prevent freezing
            if (q.size() > 10000) {
                break;
            }
        }
        al_set_target_backbuffer(al_get_current_display());
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
                        
                    }
                }
            }
            al_set_target_backbuffer(al_get_current_display());
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