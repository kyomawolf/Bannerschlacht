#include "../inc/raylib-cpp.hpp"
#include <string>

int main() {
    raylib::Image img("../circle.png");
    raylib::Window win(1080, 720, "test");
    raylib::Texture tex(img);
    raylib::Color tint = {255, 0, 0, 255};
    raylib::Camera2D cam;

    while (!win.ShouldClose()) {
        win.BeginDrawing();
        win.ClearBackground(raylib::Color::Beige());
        tex.Draw({100, 100},0, 1, tint);
        win.EndDrawing();

    }
}
