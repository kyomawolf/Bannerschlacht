#include <iostream>
#include <memory>
#include "map/Map.hpp"
#include "Parser.hpp"
#include "raylib-cpp.hpp"
#include "ui/ObjectLayer.hpp"
#include "datastructure/GameObjects.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include "units/Unit.hpp"


//int main_game_loop(Data *gameData, uiObj *ui) {
//    process();
//    render();
//}

/**
 * global variables
 */
enum scenes global_scene_var;

void    SetUpButtonsMainMenu(MenuMain& menuObject, raylib::Window& win) {
    Button      buttonNewGame( {static_cast<float>(win.GetWidth()) / 2 - 60, static_cast<float>(win.GetHeight()) / 2 - 30} , {120, 20});
    buttonNewGame.SetColor(raylib::GREEN);
    buttonNewGame.SetText("New Game");

    Button      buttonLoadGame({static_cast<float>(win.GetWidth()) / 2 - 60, static_cast<float>(win.GetHeight()) / 2 + 10} , {120, 20});
    buttonLoadGame.SetColor(raylib::ORANGE);
    buttonLoadGame.SetText("Load Game");

    Button      buttonExitGame({static_cast<float>(win.GetWidth()) / 2 - 60, static_cast<float>(win.GetHeight()) / 2 + 50} , {120, 20});
    buttonExitGame.SetColor(raylib::RED);
    buttonExitGame.SetText("Exit");
    menuObject.AddButton(buttonNewGame);
    menuObject.AddButton(buttonLoadGame);
    menuObject.AddButton(buttonExitGame);
}

void    SetUpButtonsMainUi(UiInGame& UiObject, raylib::Window& win) {
    Button      buttonVoid({static_cast<float>(win.GetWidth()) * 0.2f,
                                      static_cast<float>(win.GetHeight()) * 0.8f },
                           {static_cast<float>(win.GetWidth()) * 0.6f,
                                      static_cast<float>(win.GetHeight()) * 0.2f});
    RVector2    containerTopRightCorner = buttonVoid.GetPosition();
    RVector2    containerSize = buttonVoid.GetClickSize();
    Button      buttonEnableAttackMode({containerTopRightCorner.x + containerSize.x * 0.2f,
                                        containerTopRightCorner.y + containerSize.y * 0.5f - 60 },
                                       {60, 60 });
    buttonVoid.SetColor(raylib::BEIGE);
    buttonEnableAttackMode.SetColor(raylib::MAROON);
    UiObject.AddButton(buttonEnableAttackMode);
    UiObject.AddButton(buttonVoid); //background layer
}

int main () {
    Parser  par;
    auto   data = std::make_shared<Data>();

    try {
        par.Map("src/test.map", *data);
    } catch (Parser::ParserException &e) {
        std::cerr << e.what() << std::endl;
    }

    // replace hardcoded window settings to configuration file loading
    raylib::Window win(1080, 720, "Schlacht ver. 0.0.4");

    raylib::Image reddot(std::string("../red_dot.png"));
    std::cout << reddot.IsReady() << std::endl;
    raylib::Texture unit_text(reddot);
    std::cout << "parsed map" << std::endl;
    MapData *mapData = dynamic_cast<MapData *>(data->FindNextIdent(Data::MAP));
    Map gamemap(mapData->GetWidth(), mapData->GetHeight());
    std::cout << "loaded map" << std::endl;


    raylib::Vector2 cam_pos(win.GetWidth() / 2, win.GetHeight() / 2);
    raylib::Camera2D cam(cam_pos, raylib::Vector2(0, 0));
    win.SetTargetFPS(140);

    data->SetWindow(&win);
    MenuMain    mainGameMenu;
    UiInGame    mainUi;
    ///Main Menu Buttons:

    SetUpButtonsMainMenu(mainGameMenu, win);
    SetUpButtonsMainUi(mainUi, win);

    for (auto i = data->vecUnits.begin(); i < data->vecUnits.end(); i++) {
        try {
            gamemap.at((*i)->GetX(), (*i)->GetY()).SetEntry(*i);
            gamemap.at((*i)->GetX(), (*i)->GetY()).GetEntry()->tex = &unit_text;
            gamemap.at((*i)->GetX(), (*i)->GetY()).SetInit(true);
        } catch (...) {
            std::cout << "out of range" << std::endl;
        }
    }
    raylib::Texture quad(raylib::Image(std::string("../rectangle.png")));
//    raylib::Rectangle rec(10, 10, 700, 20);
    gamemap.SetTileTex(&quad);

    ///setting up scenes
    global_scene_var = MAINMENU;

    MainMenuScene mainMenuSceneObject(scenes::MAINMENU, win, mainGameMenu);
    GameScene     gameSceneObject(scenes::GAME, win, cam_pos, cam, data, gamemap, mainUi);

    data->vecScenes.push_back(&mainMenuSceneObject);
    data->vecScenes.push_back(&gameSceneObject);
    if (data->vecScenes.size() - 1 != scenes::ENUMCOUNT) {
#ifdef DEBUG
        std::cerr << "not every scene has been loaded: " << std::endl
        << "amount of scenes loaded: (" << data->vecScenes.size() - 1 << "/" << scenes::ENUMCOUNT << ")" << std::endl
        << "following scenes have been loaded: " << std::endl;
        for (auto &i : data->vecScenes)
            std::cerr << i->sceneType << std::endl;
#endif
        return EXIT_FAILURE;
    }
    while(!win.ShouldClose()) {
        data->getSceneByEnum(global_scene_var)->Play();
        }
    return EXIT_SUCCESS;
}
