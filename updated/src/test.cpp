//#include "../inc/raylib-cpp.hpp"
//#include <vector>
//#include <iostream>
//#include <string>
//
//#define HEIGHT	920
//#define WIDTH	1080
//
//typedef raylib::Camera2D rCamera2D;
//typedef raylib::Vector2 rVec2D;
//typedef raylib::Mouse rMouse;
//
//std::ostream&	operator<<(std::ostream& o, const rVec2D& in) {
//	o << "x: " << in.x << " | " << "y: " << in.y;
//	return o;
//}
//
//class Field {
//private:
//	static const int	hex_radius = 40;
//	int tex_width;
//	int tex_height;
//	int	width;
//	int	height;
//	const float tex_fac; //0.05
//	float tile_width;
//	float tile_height;
//public:
//	Field(int width, int height) : width(width), height(height), tex_fac(0.05) {
//		//std::vector<raylib::Vector2>(width * height, raylib::Vector2(0, 0));
//	}
//	Field(int width, int height, raylib::Texture& tex) : width(width), height(height), tex_height(tex.GetHeight()), tex_width(tex.GetWidth()), tex_fac(0.05), tile_height(tex_height * tex_fac), tile_width(tex_width * tex_fac) {
//		std::cout << "texture" << tex.GetHeight() << "  " << tex.GetWidth() << std::endl;
//		//std::vector<raylib::Vector2>(width * height, raylib::Vector2(0, 0));
//	}
//	int GetQuad(rVec2D& Tile) {
//		///if + inner quad, if - outer quad
//		float px = Tile.x - (int) Tile.x;
//		px = fabs(px - 0.5);
//		float py = Tile.y - (int) Tile.y;
//		py = fabs(py - 0.5);
//		if (px > 0.25 || py > 0.5 * 2)
//			return 0;
//		return (2 * 0.5 * 0.25 - px * 0.25 - py * 0.5) >= 0;
//	}
//
//
//	rVec2D	GetTile(rVec2D& worldpos) {
//		if (worldpos.x < 0 || worldpos.y < 0 || worldpos.x > width * tile_width || worldpos.y > height * tile_height * 1.5)
//			return rVec2D(-1,-1);
//		rVec2D Tile(worldpos.x / tile_width, worldpos.y / tile_height); //rework, wrong positions: try hexpos with only y first
//		int quad = GetQuad(Tile);
//		std::cout << "quadresult: " << quad << "    tilepos: " << Tile.x << "  " << Tile.y << std::endl;
//		if (worldpos.CheckCollision(Tile, hex_radius / 2))
//			return rVec2D(1, 1);
//		return worldpos;
//	}
//
//	raylib::Vector2	hex_pos(int x, int y) {
//		if (y % 2)
//			return raylib::Vector2(x * ((tex_width + 10) * tex_fac) + tex_width * tex_fac * 0.5, y * ((tex_height - 240) * tex_fac));
//		return raylib::Vector2(x * ((tex_width + 10) * tex_fac), y * ((tex_height - 240) * tex_fac));
//	}
//
//	void	draw(raylib::Texture& tex) {
//		int t = 0;
//		for (int x = 0; x < width; x++) {
//			for (int y = 0; y < height * 2; y++) {
////				if (x % 2){
////					if (x == 1 && y == 1)
//						if (y % 2)
//							hex_pos(x, y).DrawRectangle(rVec2D(tex.GetWidth() * tex_fac, tex.GetHeight() * tex_fac), BLUE); //bounding box for click-hit
//						else
//						hex_pos(x, y).DrawRectangle(rVec2D(tex.GetWidth() * tex_fac, tex.GetHeight() * tex_fac), RED); //bounding box for click-hit
////				}
//				tex.Draw(hex_pos(x, y), 0, tex_fac);
//			}
//		}
//	}
//	void	draw() {
//		for (int x = 0; x < width; x++) {
//			for (int y = 0; y < height * 2; y++) {
//				DrawPoly(hex_pos(x, y), 6, hex_radius, 0, raylib::Color::Red());
//				DrawPoly(hex_pos(x, y), 6, hex_radius - 3, 0, raylib::Color::LightGray());
//			}
//		}
//	}
//
//};
//
//
//void move(rVec2D& cam_pos, raylib::Window& win) {
//	if (IsKeyDown('W')) {
//		cam_pos.y -= 11 * (double) (100.0 / win.GetFPS());
//	} if (IsKeyDown('S')) {
//		cam_pos.y += 11 * (double) (100.0 / win.GetFPS());
//	} if (IsKeyDown('A')) {
//		cam_pos.x -= 11 * (double) (100.0 / win.GetFPS());
//	} if (IsKeyDown('D')) {
//		cam_pos.x += 11 * (double) (100.0 / win.GetFPS());
//	}
//}

//	raylib::Window*	win = new raylib::Window(WIDTH, HEIGHT, "test-window");
//	rVec2D	cam_pos(0,0);
//	rCamera2D cam(cam_pos, rVec2D(0,0));
//	raylib::Color textColor(BLUE);
//	win->SetTargetFPS(100);
//	raylib::Texture hexagon(raylib::Image(std::string("../pngegg.png")));
//	Field	board(10, 10, hexagon);
//	rVec2D	mousepos(0,0);
//	while (!win->ShouldClose()) {
//		win->BeginDrawing();
//		cam.BeginMode();
//		win->ClearBackground(raylib::Color::RayWhite());
//		board.draw(hexagon);
//		textColor.DrawText(std::to_string(win->GetFPS()), 200, 200, 40);
//		move(cam_pos, *win);
//		if (rMouse::IsButtonPressed(0)) {
//			mousepos = rMouse::GetPosition();
//			auto wpos = cam.GetScreenToWorld(mousepos);
//			std::cout << "mouse: " << mousepos << " Tile: " << board.GetTile(wpos) << std::endl;
//		}
//		cam.SetTarget(cam_pos);
//		cam.EndMode();
//		win->EndDrawing();
//
//	}
//	delete win;
//	return 0;
//}