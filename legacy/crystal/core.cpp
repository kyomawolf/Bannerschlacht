export module crystal.core;
//template<typename Function>

extern "C" {
#include <raylib.h>
}

#include <cstdint>

//typedef struct LinkedList {
//    void*               content;
//    struct LinkedList*  next;
//    struct LinkedList*  prev;
//} LinkedList;


namespace crystal {

    typedef uint8_t  u8;
    typedef uint32_t u32;

    class color {
    public:
        static color white;
        static color black;
        static color red;
        static color blue;
        static color green;
        static color darkgreen;

    private:
        u32  value;

    public:
        color(u8 a, u8 r, u8 g, u8 b) {
            value = (((u32) r) << 24) | (((u32) g) << 16) | (((u32) b) << 8) | ((u32) a);
        }

        color(u8 r, u8 g, u8 b) : color(0xff, r, g, b) {}

        Color as_raylib_color() {
            return GetColor(value);
        }
    };

    color color::white = color(0xff, 0xff, 0xff);
    color color::black = color(0x00, 0x00, 0x00);
    color color::red = color(0xff, 0x00, 0x00);
    color color::blue = color(0x00, 0x00, 0xff);
    color color::green = color(0x00, 0xff, 0x00);
    color color::darkgreen = color(0x00, 0x75, 0x2c);


    class rectangle {
    private:
        int x;
        int y;
        int w;
        int h;
    public:
        rectangle(int x, int y, int w, int h) {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }

        int get_x() { return x; }
        int get_y() { return y; }
        int get_w() { return w; }
        int get_h() { return h; }

        void begin_scissor() { BeginScissorMode(x, y, w, h); }
        void end_scissor()   { EndScissorMode(); }
    };

    void draw_rectangle(int x, int y, int w, int h, color the_color) {
        DrawRectangle(x, y, w, h, the_color.as_raylib_color());
    }

    void draw_rectangle(rectangle r, color the_color) {
        draw_rectangle(r.get_x(), r.get_y(), r.get_w(), r.get_h(), the_color);
    }


    class vec2D {
    private:
        Vector2  vector;
    public:
        vec2D(Vector2 v) {
            vector = v;
        }

        vec2D(float x, float y) {
            vector.x = x;
            vector.y = y;
        }

        vec2D() : vec2D(0, 0) {}

        float get_x() { return vector.x; }
        float get_y() { return vector.y; }

        void set_x(float x) { vector.x = x; }
        void set_y(float y) { vector.y = y; }
    };

    class texture {
    private:
        Texture2D  the_texture;
    public:
        texture(const char* filename) {
            the_texture = LoadTexture(filename);
        }

        void draw(float x, float y);
        void draw(vec2D);
        void draw(float x, float y, color tint);
        void draw(vec2D, color tint);
    };

    void texture::draw(float x, float y) {
        draw(x, y, color::white);
    }

    void texture::draw(vec2D pos) {
        draw(pos.get_x(), pos.get_y());
    }

    void texture::draw(float x, float y, color tint) {
        DrawTexture(the_texture, (int) x, (int) y, tint.as_raylib_color());
    }

    void texture::draw(vec2D pos, color tint) {
        draw(pos.get_x(), pos.get_y(), tint);
    }


    class camera2D {
    private:
        Camera2D  cam;
    public:
        camera2D(vec2D pos=vec2D(0, 0), float rotation=0, float zoom=1) {
            cam.offset.x = pos.get_x();
            cam.offset.y = pos.get_y();
            cam.rotation = rotation;
            cam.zoom     = zoom;
            cam.target.x = 0;
            cam.target.y = 0;
        }

        vec2D get_target() { return vec2D(cam.target); }
        vec2D get_offset() { return vec2D(cam.offset); }
        float get_scale() { return cam.zoom; }
        float get_rotation() { return cam.rotation; }

        void set_target(vec2D target) { cam.target.x = target.get_x(); cam.target.y = target.get_y(); }
        void set_offset(vec2D offset) { cam.offset.x = offset.get_x(); cam.offset.y = offset.get_y(); }
        void set_scale(float scale)   { cam.zoom = scale; }
        void set_rotation(float rot)  { cam.rotation = rot; }

        void begin() {
            BeginMode2D(cam);
        }

        void end() {
            EndMode2D();
        }
    };


    class window {
    private:
        unsigned int  width;
        unsigned int  height;

    public:
        window(unsigned int width, unsigned int height, const char* title) {
            this->width  = width;
            this->height = height;
            InitWindow(width, height, title);
        }

        ~window() {
            CloseWindow();
        }

        unsigned int get_width()  { return width; }
        unsigned int get_height() { return height; }

        bool should_close() {
            if (WindowShouldClose())
                return true;
            else
                return false;
        }

        void clear_background(color the_color) {
            ClearBackground(the_color.as_raylib_color());
        }

        void begin() {
            BeginDrawing();
        }

        void end() {
            EndDrawing();
        }

        void set_target_fps(int fps) {
            SetTargetFPS(fps);
        }
        void toggle_fullscreen(void) {
            ToggleFullscreen();
        }
        void resize_window(int width, int height) {
            SetWindowSize(width, height);
        }
    };

    class system
    {
    private:
    public:
        
        int screen_width() {
            return GetScreenWidth();
        }
        int screen_height() {
            return GetScreenHeight();
        }
        int monitor_count(){
            return GetMonitorCount();
        }
        int monitor_curr(){
            return GetCurrentMonitor();
        }
        int monitor_refresh_rate(int monitor){
            return GetMonitorRefreshRate(monitor);
        }

    };

    class cursor
    {
    private:
    public:

        void show() {
            ShowCursor();
        }
        void hide() {
            HideCursor();
        }
        void enable() {
            EnableCursor();
        }
        void disable() {
            DisableCursor();
        }
        bool is_hidden() {
            return IsCursorHidden();
        }
    };

    class input {
    public:
        bool key_pressed(int key){
            return IsKeyPressed(key);
        }
        bool key_down(int key){
            return IsKeyDown(key);
        }
        bool key_released(int key){
            return IsKeyReleased(key);
        }
        bool key_up(int key){
            return IsKeyUp(key);
        }
        void key_set_exit_key(int key){
            SetExitKey(key);
        }
        int key_get_pressed(void){
            return GetKeyPressed();
        }
        int key_get_char_pressed(void){
            return GetCharPressed();
        }
        bool mouse_pressed(int button){
            return IsMouseButtonPressed(button);
        }
        bool mouse_down(int button){
            return IsMouseButtonDown(button);
        }
        bool mouse_released(int button){
            return IsMouseButtonReleased(button);
        }
        bool mouse_up(int button){
            return IsMouseButtonUp(button);
        }
        int mouse_X(void){
            return GetMouseX();
        }
        int mouse_Y(void){
            return GetMouseY();
        }
        vec2D mouse_position(void){
            Vector2 temp = GetMousePosition();
            return vec2D(temp);
        }
        //vec2D mouse_delta(void){
        //    Vector2 temp = GetMouseDelta();
        //    return vec2D(temp);
        //}
        void mouse_setpos(int x, int y){
            SetMousePosition(x, y);
        }
        //void SetMouseOffset(int offsetX, int offsetY);
        //void SetMouseScale(float scaleX, float scaleY);
        //float GetMouseWheelMove(void);
        //void SetMouseCursor(int cursor);
    };

    //#include <string>
    //class buttonList {
    //    private:
    //    LinkedList  *buttonlist;
    //    public:
    //    buttonList();
    //    ~buttonList();
    //    int     addButton(string name, int posX, int posY, int size);
    //    int     addButton(string name, int posX, int posY, int sizeX, int sizeY);
    //    int     addButton(string name, int posX, int posY, int size, Function call);
    //    int     addButton(string name, int posX, int posY, int sizeX, int sizeY, Function call);
    //    int     addButton(string name, int posX, int posY, int size, Function call, int id);
    //    int     addButton(string name, int posX, int posY, int sizeX, int sizeY, Function call, int id);
    //    int     removeButton(string name);
    //    string  removeButton(int id);
    //    int     removeButton(int start, int range);
    //    int     hideButton(string name);
    //    string  hideButton(int id);
    //    int     hideButton(int start, int range);
    //    int     showButton(string name);
    //    string  showButton(int id);
    //    int     showButton(int start, int range);
    //    int     SetEvent(string name, Function call);
    //    string  SetEvent(int id, Function call);
    //    int     unSetEvent(string name);
    //    string  unSetEvent(int id);
    //    int     unSetEvent(int start, int range);
    //}
}
