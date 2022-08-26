#include "data.hpp"
#include "raylib-cpp.hpp"

int main_game_loop(data *gameData, uiObj *ui) {
    process();
    render();
}

int main () {
    data* gameData = new data(/*config file?*/);
    return main_game_loop(gameData, uiStartup());
}