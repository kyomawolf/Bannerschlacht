#include <iostream>
#include <memory>
#include "map/Map.hpp"
#include "Parser.hpp"
#include "raylib-cpp.hpp"
#include "ui/ObjectLayer.hpp"
#include "datastructure/GameObjects.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include <unistd.h>
#include "units/Unit.hpp"


//int main_game_loop(Data *gameData, uiObj *ui) {
//    process();
//    render();
//}

/**
 * global variables
 */
enum scenes global_scene_var;

void    SetUpButtonsMainMenu(MenuMain& menuObject, std::unique_ptr<raylib::Window>& win) {
    Button      buttonNewGame( {static_cast<float>(win->GetWidth()) / 2 - 60, static_cast<float>(win->GetHeight()) / 2 - 30} , {120, 20});
    buttonNewGame.SetColor(raylib::GREEN);
    buttonNewGame.SetText("New Game");

    Button      buttonLoadGame({static_cast<float>(win->GetWidth()) / 2 - 60, static_cast<float>(win->GetHeight()) / 2 + 10} , {120, 20});
    buttonLoadGame.SetColor(raylib::ORANGE);
    buttonLoadGame.SetText("Load Game");

    Button      buttonExitGame({static_cast<float>(win->GetWidth()) / 2 - 60, static_cast<float>(win->GetHeight()) / 2 + 50} , {120, 20});
    buttonExitGame.SetColor(raylib::RED);
    buttonExitGame.SetText("Exit");
    menuObject.AddButton(buttonNewGame);
    menuObject.AddButton(buttonLoadGame);
    menuObject.AddButton(buttonExitGame);
}

void    NextRound() {
    std::cout << "next round" << std::endl;
    for (auto& currentPlayer : Data::GetInstance().GetPlayerCollection()) {
        currentPlayer->Routine();
        for (auto &i : Data::GetInstance().GetUnitCollection()) {
            if (i->GetPlayer() == currentPlayer->GetId())
            i->Action();
        }
    }
}

void    SetUpButtonsMainUi(UiInGame& UiObject, std::unique_ptr<raylib::Window>& win) {
    Button      buttonVoid({static_cast<float>(win->GetWidth()) * 0.2f,
                                      static_cast<float>(win->GetHeight()) * 0.8f },
                           {static_cast<float>(win->GetWidth()) * 0.6f,
                                      static_cast<float>(win->GetHeight()) * 0.2f});
    RVector2    containerTopRightCorner = buttonVoid.GetPosition();
    RVector2    containerSize = buttonVoid.GetClickSize();
    Button      buttonEnableAttackMode({containerTopRightCorner.x + containerSize.x * 0.2f,
                                        containerTopRightCorner.y + containerSize.y * 0.5f - 60 },
                                       {60, 60 });
    Button      buttonNextRound({containerTopRightCorner.x + containerSize.x - 100,
                                 containerTopRightCorner.y + containerSize.y * 0.5f - 60 },
                                {60, 60});

    buttonNextRound.SetCallableFunction(NextRound);

    buttonNextRound.SetColor(raylib::LIME);
    buttonVoid.SetColor(raylib::BEIGE);
    buttonEnableAttackMode.SetColor(raylib::MAROON);
    UiObject.AddButton(buttonEnableAttackMode);
    UiObject.AddButton(buttonNextRound);
    UiObject.AddButton(buttonVoid); //background layer
}

//int Setup() {
//}

int main (int argc, char **argv) {
    Data &data = Data::GetInstance();
    if (argc == 2)
        data.SetGameSettings(Parser::Settings(argv[1]));
    else
        data.SetGameSettings(Parser::Settings());
    try {
        std::cout << "parsing map" << std::endl;
        Parser::Map("src/test.map", data); //todo refactor (change parameters)
    } catch (Parser::ParserException &e) {
        std::cout << "exception caught: " << std::endl;
        std::cerr << e.what() << std::endl;
    }
    std::cout << data.GetMapCollection().size() << std::endl;
    // replace hardcoded window settings to configuration file loading
    data.InitWindow(1080, 720, "Schlacht ver. 0.0.4");

    raylib::Image redDot(data.GetGameSettings().textureList.find("unit_base_graphic")->second); //todo refactor image finding
    raylib::Image quadImage(data.GetGameSettings().textureList.find("tile_base_graphic")->second);
    raylib::Image unitTestImage(data.GetGameSettings().textureList.find("unit_test_graphic")->second);
    raylib::Texture quad(quadImage); ///todo make unique and move into map (or better said, move the loading of texture also into the maploading
    data.GetMapDataByIdx(0).GetMapPointer()->SetTileTex(&quad);
//    raylib::Image reddot(std::string("../red_dot.png"));
    std::cout << redDot.IsReady() << std::endl;
    raylib::Texture unit_texture(redDot);
    raylib::Texture unitTestTexture(unitTestImage);
    data.AddImageCollection(redDot);
    data.AddImageCollection(unitTestImage);
    data.AddTextureCollection("tile_base_graphic", unit_texture);
    data.AddTextureCollection("unit_test_graphic", unitTestTexture);
    std::cout << "parsed map" << std::endl;
//    MapData *mapData = dynamic_cast<MapData *>(data->FindNextIdent(Data::MAP));
//    Map gamemap(mapData->GetWidth(), mapData->GetHeight());
    std::cout << "loaded map" << std::endl;


    raylib::Vector2 cam_pos(data.GetWindow()->GetWidth() / 2, data.GetWindow()->GetHeight() / 2);
    raylib::Camera2D cam(cam_pos, raylib::Vector2(0, 0));
    data.GetWindow()->SetTargetFPS(140);

    MenuMain    mainGameMenu;
    UiInGame    mainUi;
    SetUpButtonsMainMenu(mainGameMenu, data.GetWindow());
    SetUpButtonsMainUi(mainUi, data.GetWindow());
    data.AddVecScenes(std::make_unique<MainMenuScene>(scenes::MAINMENU, mainGameMenu));
    data.AddVecScenes(std::make_unique<GameScene>(scenes::GAME, cam_pos, cam, mainUi, 0));
    Pathfinder paths(data.GetMapDataByIdx(0).GetMapPointer());
    std::cout << "generating path..." << std::endl;
    paths.GeneratePath({0 ,0}, {1, 3});
    exit(0);
//    data.getSceneByEnum(scenes::GAME);
//    data->SetWindow(&win);


//    raylib::Rectangle rec(10, 10, 700, 20);
//    gamemap.SetTileTex(&quad);

    ///setting up scenes
    global_scene_var = MAINMENU;

//    MainMenuScene mainMenuSceneObject(scenes::MAINMENU, win, mainGameMenu);
//    GameScene     gameSceneObject(scenes::GAME, cam_pos, cam, data, mainUi, mapID);

//    data->vecScenes.push_back(&mainMenuSceneObject);
//    data->vecScenes.push_back(&gameSceneObject);

    for (auto i=0; i != 20; i++) {
        for (auto ii = 0; ii != 20; ii++) {
            std::cout << data.GetMapDataByIdx(0).GetMapPointer()->at(i, ii).GetEntry() << " ";
        }
        std::cout << std::endl;
    }

    for (auto &i : data.GetUnitCollection()) {
//        if (i == nullptr)
//            continue;
        std::cout << "unit" << i->GetX() << " " << i->GetY() << std::endl;
    }

    while(!data.GetWindow()->ShouldClose()) {
        data.getSceneByEnum(global_scene_var).Play();
        }
    return EXIT_SUCCESS;
}
