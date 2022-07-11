#include "../inc/raylib-cpp.hpp"
#include <vector>
#include <iostream>
#include <string>

#define HEIGHT	920
#define WIDTH	1080

typedef raylib::Camera2D rCamera2D;
typedef raylib::Vector2 rVec2D;

class Field {
private:
	static const int	hex_radius = 40;
	int	width;
	int	height;
public:
	Field(int width, int height) : width(width), height(height) {
		//std::vector<raylib::Vector2>(width * height, raylib::Vector2(0, 0));
	}

	raylib::Vector2	hex_pos(int x, int y) {
		if (y % 2)
			return raylib::Vector2(x * (hex_radius * (2)) + hex_radius * 1, y * (hex_radius * 0.55));
		return raylib::Vector2(x * (hex_radius * (2)), y * (hex_radius * 0.55));
	}

	void	draw(raylib::Texture& tex) {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				tex.Draw(hex_pos(x, y), 0, 0.05);
			}
		}
	}
	void	draw() {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				DrawPoly(hex_pos(x, y), 6, hex_radius, 0, raylib::Color::Red());
				DrawPoly(hex_pos(x, y), 6, hex_radius - 3, 0, raylib::Color::LightGray());
			}
		}
	}

};

int main () {
	raylib::Window*	win = new raylib::Window(WIDTH, HEIGHT, "test-window");
	rVec2D	cam_pos(0,0);
	rCamera2D cam(cam_pos, rVec2D(0,0));
	raylib::Color textColor(BLUE);
	Field	board(200, 200);
	win->SetTargetFPS(120);
	raylib::Texture hexagon(raylib::Image(std::string("../pngegg.png")));

	while (!win->ShouldClose()) {
		win->BeginDrawing();
		cam.BeginMode();
		win->ClearBackground(raylib::Color::RayWhite());
		board.draw(hexagon);
		textColor.DrawText(std::to_string(win->GetFPS()), 200, 200, 40);
		if (IsKeyDown('W')) {
			cam_pos.y -= 11;
		} if (IsKeyDown('S')) {
			cam_pos.y += 11;
		} if (IsKeyDown('A')) {
			cam_pos.x -= 11;
		} if (IsKeyDown('D')) {
			cam_pos.x += 11;
		}
		cam.SetTarget(cam_pos);
		cam.EndMode();
		win->EndDrawing();

	}
	delete win;
	return 0;
}