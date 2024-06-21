#include "canvas.hpp"
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <queue>
#include "Engine/Point.hpp"
#include "UI/Component/ImageButton.hpp" // Include the header file for Engine::ImageButton
u_int32_t get_pixel(ALLEGRO_COLOR c) {
    return (uint32_t)(c.r * 255) << 24 | (uint32_t)(c.g * 255) << 16 | (uint32_t)(c.b * 255) << 8 | (uint32_t)(c.a * 255);
}
void bucket_fill(ALLEGRO_BITMAP* bitmap, int start_x, int start_y, ALLEGRO_COLOR fill_color) {
    ALLEGRO_LOCKED_REGION* locked_region = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READWRITE);
    if (!locked_region) {
        std::cerr << "Failed to lock bitmap for bucket fill!" << std::endl;
        return;
    }
    //std::cout<<"fill color = "<<fill_color.r<<" "<<fill_color.g<<" "<<fill_color.b<<std::endl;
    int width = al_get_bitmap_width(bitmap);
    int height = al_get_bitmap_height(bitmap);
    ALLEGRO_COLOR target_color = al_get_pixel(bitmap, start_x, start_y);

    std::queue<std::pair<int, int>> q;
    q.push({start_x, start_y});

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x < 0 || x >= width || y < 0 || y >= height) continue;

        ALLEGRO_COLOR current_color = al_get_pixel(bitmap, x, y);
        if (current_color.r == fill_color.r && current_color.g == fill_color.g && current_color.b == fill_color.b) continue;

        if (current_color.r == target_color.r && current_color.g == target_color.g && current_color.b == target_color.b) {
            uint32_t* pixel = (uint32_t*)((uint8_t*)locked_region->data + y * locked_region->pitch) + x;
            //convert rgba to uint32_t
            *pixel = get_pixel(al_map_rgb(fill_color.r, fill_color.g, fill_color.b));
            q.push({x+1, y});
            q.push({x-1, y});
            q.push({x, y+1});
            q.push({x, y-1});
        }
    }

    al_unlock_bitmap(bitmap);
}
canvas::canvas() {
    std::cout<<"creating canvas"<<std::endl;
    this->visible = true;
    this->paint_brush_size = 1;
    canvasBitmap = al_create_bitmap(canvasWidth, canvasHeight);
    al_set_target_bitmap(canvasBitmap);
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Initialize with a default color
    al_set_target_backbuffer(al_get_current_display()); // Reset target to backbuffer
}
bool canvas::color_compare(ALLEGRO_COLOR b, int x, int y) {
    ALLEGRO_COLOR c = al_get_pixel(canvasBitmap, x, y);
    return c.r == b.r && c.g == b.g && c.b == b.b; // Ensure this comparison is valid
}
void canvas::OnMouseDown(int button, int mx, int my) {
    if (button == 1) {
        if(mouseIn && !bucket_switch){
            isMousePressed = true;
        }
        if(bucket_switch){
            int canvasX = mx/2;
            int canvasY = my/2;
            std::cout<<"paint brush color = "<<paint_brush_color.r<<" "<<paint_brush_color.g<<" "<<paint_brush_color.b<<std::endl;
            bucket_fill(this->canvasBitmap, canvasX, canvasY, this->paint_brush_color);
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
            al_set_target_bitmap(canvasBitmap);
            
            for (int offsetY = -brush_size/2; offsetY <= brush_size/2; ++offsetY) {
                for (int offsetX = -brush_size/2; offsetX <= brush_size/2; ++offsetX) {
                    int paintX = canvasX + offsetX;
                    int paintY = canvasY + offsetY;
                    // Ensure the paint position is within the canvas bounds
                    if (paintX >= 0 && paintX < canvasWidth && paintY >= 0 && paintY < canvasHeight) {
                        // Set the pixel color to black
                        if(eraser_switch==0)al_draw_pixel(paintX, paintY, paint_brush_color);
                        else al_draw_pixel(paintX, paintY, al_map_rgb(0, 0, 0));
                        
                    }
                }
            }
            al_set_target_backbuffer(al_get_current_display());
        }
    } else {
        mouseIn = false;
    }
    ALLEGRO_BITMAP* Target = al_get_target_bitmap();
    if(this->bucket_switch){
        Target = ALLEGRO_BITMAP* bucketImage = Engine::Resources::GetInstance().GetBitmap("bucket1.png");
    }else if(this->eraser_switch){
        Target = ALLEGRO_BITMAP* eraserImage = Engine::Resources::GetInstance().GetBitmap("eraser1.png");
    }else{
        Target = ALLEGRO_BITMAP* paintBrushImage = Engine::Resources::GetInstance().GetBitmap("bucket1.png");
    }
    al_draw_scale_bitmap(Target, mx, my, 0);
    //FIXME: Implement the mouse cursor change when the eraser or bucket tool is selected
}
void canvas::Draw() const {
    al_draw_scaled_bitmap(canvasBitmap,
                          0, 0, canvasWidth, canvasHeight, // source bitmap region
                          0, 0, 2 * canvasWidth, 2 * canvasHeight, // target display region
                          0); // flags
}
void canvas::setBrushSize(int size){
    this->paint_brush_size = size;
}
int canvas::getBrushSize() const{
    return this->paint_brush_size;
}
canvas::~canvas() {
    if (canvasBitmap) {
        al_destroy_bitmap(canvasBitmap);
    }
}
void canvas::setBrushColor(ALLEGRO_COLOR color){
    this->paint_brush_color = color;
}
ALLEGRO_BITMAP* canvas::getBitmap() const{
    return this->canvasBitmap;
}