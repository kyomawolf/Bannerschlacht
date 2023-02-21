#ifndef DATA_HPP
#define DATA_HPP

#include "raylib-cpp.hpp"
#include <memory>
#include <vector>
#include "BaseData.hpp"
#include "../Scene.hpp"
#include "../Player.hpp"
#include "../algorithm/PathFinder.hpp"

#include "../units/Unit.hpp"
#include "Setting.hpp"
class Scene;

class Data {
public:
    struct InputCollection {
        int     pressedKey;
        int     mouseButton;
    };
private:

// make sure to call Window.init()
    InputCollection                         _input;
    std::unique_ptr<raylib::Window>         _window{nullptr};
    std::vector<raylib::Image>              imageCollection;
    std::map<std::string, raylib::Texture&> textureCollection;
    std::vector<std::shared_ptr<Player>>    playerCollection;
    std::vector<MapData>                    mapCollection{};
    std::vector<std::shared_ptr<UnitData>>  unitCollection{(0, 0, 0, 0, 0, -1, 0, 0, 0, nullptr)};
    std::vector<TileData>                   vecTiles;
    std::vector<std::unique_ptr<Scene>>     vecScenes;
    Pathfinder                              pathCollection;
    Setting                                 gameSettings;

    static Data _instance;
    static int  _mapIndex;

public:
    //all data will be held here
    //use generator function to create pointer to DataLinkobject
    //use generator function to create a vector list of all pointer of same classtype
    Scene& getSceneByEnum(scenes type);

    [[nodiscard]] std::unique_ptr<raylib::Window>& GetWindow();

    bool     InitWindow(int width, int height, const std::string& title);

    [[nodiscard]] const std::vector<raylib::Image> &GetImageCollection() const;

    [[nodiscard]] const std::map<std::string, raylib::Texture&> &GetTextureCollection() const;

    void AddTextureCollection(std::string name, raylib::Texture &textureCollection);

    [[nodiscard]] const std::vector<std::unique_ptr<Scene>> &GetVecScenes() const;

    void AddVecScenes(std::unique_ptr<Scene> scene);

    void AddImageCollection(raylib::Image &imageCollection);

    void AddUnitToCollection(std::shared_ptr<UnitData> &unitToAdd);

    int AddMapToCollection(MapData &mapToAdd);

    const Setting &GetGameSettings() const;

    void SetGameSettings(const Setting &settings);

    const std::vector<std::shared_ptr<UnitData>> &GetUnitCollection() const;

    void SetUnitCollection(std::vector<std::shared_ptr<UnitData>> unitCollection);

    void    UpdatePathfinder();

    Pathfinder& GetPathfinder();

    std::vector<std::shared_ptr<Player>> &GetPlayerCollection();
    void AddPlayerToCollection(std::shared_ptr<Player> &singlePlayer);

    int DefaultAddUnit();

    void ClearUnits();

    std::shared_ptr<UnitData>& GetUnit(int id);

    const std::vector<MapData> &GetMapCollection() const;

    MapData& GetMapDataByIdx(size_t idx);

    raylib::Texture& GetTexture(std::string& name) const;

    std::shared_ptr<UnitData>   GetUnitByLocation(TileIndex index);
    std::shared_ptr<Player>     GetPlayerById(int id);

    const InputCollection &GetInput() const;

    void SetInput();

//    void SetMapCollection(const std::vector<MapData> &mapCollection);

    Data();
    ~Data();

    static Data &GetInstance();

};

#endif /*DATA_HPP*/