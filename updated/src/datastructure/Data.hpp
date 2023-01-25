#ifndef DATA_HPP
#define DATA_HPP

#include "raylib-cpp.hpp"
#include <memory>
#include <vector>
#include "BaseData.hpp"
#include "../Scene.hpp"
#include "../units/Unit.hpp"
#include "Setting.hpp"
class Scene;

class Data {
public:
private:

// make sure to call Window.init()
    std::unique_ptr<raylib::Window>     _window{nullptr};
    std::vector<raylib::Image>          imageCollection;
    std::vector<raylib::Texture>        textureCollection;
    std::vector<MapData>                mapCollection{};
    std::vector<std::shared_ptr<UnitData>>    unitCollection{(0, 0, 0, 0, 0, -1, 0, 0, 0, nullptr)};
    std::vector<TileData>               vecTiles;
    std::vector<std::unique_ptr<Scene>> vecScenes; //TODO make private
    Setting                             gameSettings;

    static Data instance;

public:
    //all data will be held here
    //use generator function to create pointer to DataLinkobject
    //use generator function to create a vector list of all pointer of same classtype
    //TODO make private
    Scene& getSceneByEnum(scenes type);

    [[nodiscard]] std::unique_ptr<raylib::Window>& GetWindow();

    bool     InitWindow(int width, int height, const std::string& title);

    [[nodiscard]] const std::vector<raylib::Image> &GetImageCollection() const;

    [[nodiscard]] const std::vector<raylib::Texture> &GetTextureCollection() const;

    void AddTextureCollection(raylib::Texture &textureCollection);

    [[nodiscard]] const std::vector<std::unique_ptr<Scene>> &GetVecScenes() const;

    void AddVecScenes(std::unique_ptr<Scene> scene);

    void AddImageCollection(raylib::Image &imageCollection);

    void AddUnitToCollection(std::shared_ptr<UnitData> &unitToAdd);

    void AddMapToCollection(MapData &mapToAdd);

    const Setting &GetGameSettings() const;

    void SetGameSettings(const Setting &settings);

    const std::vector<std::shared_ptr<UnitData>> &GetUnitCollection() const;

    void SetUnitCollection(std::vector<std::shared_ptr<UnitData>> unitCollection);

    int DefaultAddUnit();

    std::shared_ptr<UnitData>& GetUnit(int id);

    const std::vector<MapData> &GetMapCollection() const;

    MapData& GetMapDataByIdx(size_t idx);

//    void SetMapCollection(const std::vector<MapData> &mapCollection);

    Data();
    ~Data();

    static Data &GetInstance();
};

#endif /*DATA_HPP*/